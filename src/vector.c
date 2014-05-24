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

bool v_is_zero (vector v)
{
    return d_is_zero (v.x) && d_is_zero (v.y) && d_is_zero (v.z);
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
        a.x * b.y - a.y * b.x
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

static inline double _det_3 (vector a, vector b, vector c)
{
    /* Déterminant:
     *  | a_x   b_x   c_x |
     *  | a_y   b_y   c_y |
     *  | a_z   b_z   c_z |
     */
    double det  = a.x * d_det (b.y, b.z, c.y, c.z);
    det -= a.y * d_det (b.x, b.z, c.x, c.z);
    det += a.z * d_det (b.x, b.y, c.x, c.y);

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
    return v_dot (p, u) * v_length (u);
}

vector v_recompose (double x, double y, double z, vector u, vector v, vector w)
{
    vector x_u = v_multiply (x, u);
    vector y_v = v_multiply (y, v);
    vector z_w = v_multiply (z, w);
    vector result = v_add (v_add (x_u, y_v), z_w);

    return result;
}

static inline bool _v_col (vector a, vector b)
{
    vector cross = v_cross (a, b);
    return v_is_zero (cross);
}

void v_ux_uy_from_uz (vector u_z, vector * const u_x, vector * const u_y)
{
    /* Voir sujet. */
    vector j = v_new (0.0, 1.0, 0.0);

    if (_v_col (j, u_z))
    {
        if (u_z.y > 0)
        {
            * u_x = v_new (1.0, 0.0, 0.0);
            * u_y = v_new (0.0, 0.0, -1.0);
        }
        else
        {
            * u_x = v_new (-1.0, 0.0, 0.0);
            * u_y = v_new (0.0, 0.0, -1.0);
        }
    }
    else
    {
        * u_y = v_unit (v_cross (j, u_z));
        * u_x = v_unit (v_cross (* u_y, u_z));
    }
}

static inline vector _v_decompose_v (vector v, vector i, vector j, vector k)
{
    return v_new
    (
        v_decompose (v, i),
        v_decompose (v, j),
        v_decompose (v, k)
    );
}

static inline vector _v_recompose_v (vector v, vector i, vector j, vector k)
{
    return v_recompose (v.x, v.y, v.z, i, j, k);
}

vector v_rotate (point p, point centre, point a, point b)
{
    vector a_x, a_y, b_x, b_y;
    vector a_z = v_unit (v_add (centre, a));
    vector b_z = v_unit (v_add (centre, b));
    v_ux_uy_from_uz (a_z, & a_x, & a_y);
    v_ux_uy_from_uz (b_z, & b_x, & b_y);

    vector p_in_a = _v_decompose_v (p, a_x, a_y, a_z);

    return _v_recompose_v (p_in_a, b_x, b_y, b_z);
}

vector v_rotate_2 (point p, point centre, point a, point b)
{
    vector a_x = v_new (0.0, 0.0, 0.0);
    vector a_y = v_new (0.0, 0.0, 0.0);
    vector b_x = v_new (0.0, 0.0, 0.0);
    vector b_y = v_new (0.0, 0.0, 0.0);
    vector a_z = v_unit (a);
    vector b_z = v_unit (b);
    v_ux_uy_from_uz (a_z, & a_x, & a_y);
    v_ux_uy_from_uz (b_z, & b_x, & b_y);
    vector p_in_a = v_substract (p, centre);
    p_in_a = _v_decompose_v (p_in_a, a_x, a_y, a_z);
    p_in_a = _v_recompose_v (p_in_a, b_x, b_y, b_z);
    p_in_a = v_add (p_in_a, centre);

    return p_in_a;
}
