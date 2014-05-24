/**
 * \file vector.c
 * \brief Vector.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#include "vector.h"

vector v_new (double x, double y, double z)
{
    return (vector) { .x = x, .y = y, .z = z };
}

/* Functionnal programming RPZ !
 * v_map_1 : appliquer "op" ou "f" sur chaque coordonnée du vecteur v.
 * v_map_2 : appliquer "op" ou "f" sur les coordonnées 2 à 2 des vecteurs a et b.
 * v_fold : fold.
 */
#define v_map_1_op(op, v) v_new (v.x op, v.y op, v.z op)
#define v_map_1_f(f, v) v_new (f (v.x), f (v.y), f (v.z))
#define v_map_2_op(op, a, b) v_new (a.x op b.x, a.y op b.y, a.z op b.z)
#define v_map_2_f(f, a, b) v_new (f (a.x, b.x), f (a.y, b.y), f (a.z, b.z))
#define v_fold_op(op, v) v.x op v.y op v.z

void v_print (vector v, const char * message)
{
    #ifdef __ENABLE_DEBUG
        if (message != NULL)
            fprintf (stderr, "%s: ", message);
        fprintf (stderr, "(%f, %f, %f)\n", v.x, v.y, v.z);
    #endif
}


vector v_add (vector a, vector b)
{
    return v_map_2_op (+, a, b);
}

vector v_substract (vector a, vector b)
{
    return v_map_2_op (-, a, b);
}

vector v_multiply (double lambda, vector v)
{
    return v_map_1_op (* lambda, v);
}

vector v_cross (vector a, vector b)
{
    return v_new
    (
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.y
    );
}

double v_dot (vector a, vector b)
{
    vector a_times_b = v_map_2_op (*, a, b);
    return v_fold_op (+, a_times_b);
}

double v_length (vector v)
{
    vector coordinates_squares = v_map_1_f (d_square, v);
    double squares_sum = v_fold_op (+, coordinates_squares);
    return sqrt (squares_sum);
}

vector v_unit (vector v)
{
    double length = v_length (v);
    return v_map_1_op (/ length, v);
}

static inline double _det_2 (double a_x, double a_y, double b_x, double b_y)
{
    /* Déterminant:
     *  | a_x   b_x |
     *  | a_y   b_y |
     */
    return a_x * b_y - a_y * b_x;
}

static inline double _det_3 (vector a, vector b, vector c)
{
    /* Déterminant:
     *  | a_x   b_x   c_x |
     *  | a_y   b_y   c_y |
     *  | a_z   b_z   c_z |
     */
    double det  = a.x * _det_2 (b.y, b.z, c.y, c.z);
    det -= a.y * _det_2 (b.x, b.z, c.x, c.z);
    det += a.z * _det_2 (b.x, b.y, c.x, c.y);

    return det;
}

static inline bool _orientation (point a, point b)
{
    return a.y > a.y || (b.y == a.y && a.x < b.x);
}

bool v_is_on_the_right (point m, point a, point b)
{
    return _orientation (a, b) ? _det_3 (a, b, m) : _det_3 (b, a, m);
}

bool v_segments_intersect (point a, point b, point c, point d)
{
    double det_1 = _det_3 (a, b, c);
    double det_2 = _det_3 (a, b, d);
    double det_3 = _det_3 (c, d, a);
    double det_4 = _det_3 (c, d, b);

    return d_is_zero (det_1)
        || d_is_zero (det_2)
        || d_is_zero (det_3)
        || d_is_zero (det_4)
        || (det_1 * det_2 < 0 && det_3 * det_4 < 0)
    ;
}

static inline double _distance (point a, point b)
{
    vector a_minus_b = v_substract (a, b);
    vector squares = v_map_1_f (d_square, a_minus_b);
    double squares_sum = v_fold_op (+, squares);

    return sqrt (squares_sum);
}

bool v_ray_intersects_segment (point m, vector u_ray, point a, point b)
{
    /* Méthode stupide :
     * Construction du segment [MN] avec N tel que :
     * - |MN| > max (|MA|, |MB|)
     * - MN de même direction que u_ray.
     */

    double lambda = fmax (_distance (m, a), _distance (m, b));
    lambda = lambda / v_length (u_ray) + 1;
    vector n = v_add (m, v_multiply (lambda, u_ray));

    return v_segments_intersect (m, n, a, b);
}

vector v_turn_around_y (vector v, double angle)
{
    /* Rotation autour de l'axe Y:
     *  (   cos a   0   sin a ) ( v.x )
     *  (   0       1   0     ) ( v.y )
     *  (   -sin a  0   cos a ) ( v.z )
     */

    return v_new
    (
        v.x * cos (angle) + v.z * sin (angle),
        v.y,
        v.x * (-1) * sin (angle) + v.z * cos (angle)
    );
}

vector v_turn_around_z (vector v, double angle)
{
    /* Rotation autour de l'axe Y:
     *  (   cos a   -sin a  0 ) ( v.x )
     *  (   sin a   cos a   0 ) ( v.y )
     *  (   0       0       1 ) ( v.z )
     */

    return v_new
    (
        v.x * cos (angle) + v.y * (-1) * sin (angle),
        v.x * sin (angle) + v.y * cos (angle),
        v.z
    );
}

vector v_project_on_plane (vector v, vector normal)
{
    /* 1. Vecteurs i, j de la base (i, j, k), avec k = normal.
     * 2. Coordonnées x, y de v dans la base (i, j, k).
     * 3. Recomposition du nouveau vecteur de coordonnées (x, y, 0) dans (i, j, k).
     */
    vector u_x = v_new (0.0, 0.0, 0.0);
    vector u_y = v_new (0.0, 0.0, 0.0);
    v_ux_uy_from_uz (normal, & u_x, & u_y);
    double x = v_decompose (v, u_x);
    double y = v_decompose (v, u_y);

    return v_recompose (x, y, 0.0, u_x, u_y, normal);
}

double v_decompose (vector p, vector u)
{
    return v_dot (p, u);
}

vector v_recompose (double x, double y, double z, vector u, vector v, vector w)
{
    vector x_u = v_multiply (x, u);
    vector y_v = v_multiply (y, v);
    vector z_w = v_multiply (z, w);
    vector result = v_add (v_add (x_u, y_v), z_w);

    return result;
}
