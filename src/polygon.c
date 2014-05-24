/**
 * \file polygon.c
 * \brief Polygon.
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
#include "polygon.h"

polygon * p_new (void)
{
    polygon * const p = malloc (sizeof * p);

    if (p != NULL)
    {
        p->_nb_vertices = 0;
        p->_is_closed = false;
        p->_is_filled = false;
        p->_is_convex = false;
    }
    else
    {
        perror ("malloc");
    }

    return p;
}

void p_copy (const polygon * const original, polygon * const copy)
{
    if (original != NULL && copy != NULL && original != copy)
    {
        for (int i = 0; i < original->_nb_vertices; ++i)
            copy->_vertices[i] = original->_vertices[i];

        copy->_nb_vertices = original->_nb_vertices;
        copy->_is_closed = original->_is_closed;
        copy->_is_filled = original->_is_filled;
        copy->_is_convex = original->_is_convex;
    }
}

void p_add_vertex (polygon * const p, point v)
{
    if (p != NULL && p->_nb_vertices < P_MAX_VERTICES)
    {
        p->_vertices[p->_nb_vertices] = v;
        p->_nb_vertices++;
    }
}

void p_remove_last_vertex (polygon * const p)
{
    if (p != NULL && p->_nb_vertices > 0)
        p->_nb_vertices--;
}

void p_print (const polygon * const p, const char * const message)
{
    #ifdef __ENABLE_DEBUG
        if (message != NULL)
            fprintf (stderr, "%s:\n", message);

        if (p != NULL)
        {
            fprintf
            (
                stderr,
                "%sclosed, %sfilled, %sconvex, %d vertices.\n",
                p->_is_closed ? "" : "not ",
                p->_is_filled ? "" : "not ",
                p->_is_convex ? "" : "not ",
                p->_nb_vertices
            );

            for (int i = 0; i < p->_nb_vertices; ++i)
            {
                fprintf (stderr, "\t");
                v_print (p->_vertices[i], NULL);
            }
        }
    #endif
}

void p_draw (const polygon * const p, int width, int height)
{
}

bool p_is_closed (const polygon * const p)
{
    return p->_is_closed;
}

bool p_is_filled (const polygon * const p)
{
    return p->_is_filled;
}

bool p_is_convex (const polygon * const p)
{
    return p->_is_convex;
}

bool p_is_on_the_left_of_all_edges (const polygon * const p, point m)
{
    bool result = p->_nb_vertices > 1;

    for (int i = 0; result && i < p->_nb_vertices - 1; ++i)
        result = ! v_is_on_the_right (m, p->_vertices[i], p->_vertices[i + 1]);

    return result;
}

int p_nb_edges_intersected_by_ray (const polygon * const p, point m, vector u_ray)
{
    int count = 0;

    if (p->_nb_vertices > 1)
        for (int i = 0; i < p->_nb_vertices - 1; ++i)
            if (v_ray_intersects_segment (m, u_ray, p->_vertices[i], p->_vertices[i + 1]))
                ++count;

    return count;
}

bool p_is_inside (const polygon * const p, point m)
{
    vector h = v_new (1.0, 0.0, 0.0);
    return (p_nb_edges_intersected_by_ray (p, m, h) % 2) == 1;
}

void p_turn_around_y (polygon * const p, double angle)
{
    for (int i = 0; i < p->_nb_vertices; ++i)
        v_turn_around_y (p->_vertices[i], angle);
}

vector p_center (const polygon * p)
{
    vector center = v_new (0.0, 0.0, 0.0);

    if (p->_nb_vertices > 0)
    {
        for (int i = 0; i < p->_nb_vertices; ++i)
            center = v_add (center, p->_vertices[i]);
        center = v_multiply ((float) 1 / p->_nb_vertices, center);
    }

    return center;
}

vector p_normal (const polygon * const p)
{
    vector result = v_new (0.0, 0.0, 0.0);

    if (p->_nb_vertices > 2)
    {
        vector a = v_substract (p->_vertices[1], p->_vertices[0]);
        vector b = v_substract (p->_vertices[2], p->_vertices[1]);
        result = v_unit (v_cross (a, b));
    }

    return result;
}

void p_scale (polygon * const p, double factor)
{
    if (p->_nb_vertices > 1)
    {
        vector vertices[p->_nb_vertices];

        vertices[0] = p->_vertices[0];
        for (int i = 1; i < p->_nb_vertices; ++i)
        {
            vector edge = v_substract (p->_vertices[i], p->_vertices[i - 1]);
            vector new_edge = v_multiply (factor, edge);
            vertices[i] = v_add (vertices[i - 1], new_edge);
        }

        for (int i = 1; i < p->_nb_vertices; ++i)
            p->_vertices[i] = vertices[i];
    }
}

void p_translate (polygon * const p, vector trans)
{
    for (int i = 0; i < p->_nb_vertices; ++i)
        p->_vertices[i] = v_add (p->_vertices[i], trans);
}

void p_rotate (polygon * const p, vector normal)
{
    vector center = p_center (p);
    vector current_normal = p_normal (p);
    for (int i = 0; i < p->_nb_vertices; ++i)
        p->_vertices[i] = v_rotate (p->_vertices[i], center, current_normal, normal);
}
