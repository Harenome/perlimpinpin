/**
 * \file mesh.c
 * \brief Mesh.
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
#include "mesh.h"

mesh * m_new (void)
{
    mesh * const m = malloc (sizeof * m);

    if (m != NULL)
        m_init (m);
    else
        perror ("malloc");

    return m;
}

void m_init (mesh * const m)
{
    if (m != NULL)
    {
        m->_nb_quads = 0;
        m->_is_filled = 0;
    }
}

void m_print (const mesh * const m, const char * const message)
{
    #ifdef __ENABLE_DEBUG
        if (message != NULL)
            fprintf (stderr, "%s:\n", message);
        if (m != NULL)
        {
            fprintf
            (
                stderr,
                "%sfilled, %d quads.\n",
                m->_is_filled ? "" : "not ",
                m->_nb_quads
            );
            for (int i = 0; i < m->_nb_quads; ++i)
                q_print (& m->_quads[i], NULL);
        }
    #endif
}

void m_add_quad (mesh * const m, quad q)
{
    if (m != NULL && m->_nb_quads < M_MAX_QUADS)
    {
        m->_quads[m->_nb_quads] = q;
        m->_nb_quads++;
    }
}

void m_add_slice (mesh * const m, const polygon * const p1, const polygon * const p2)
{
    if (m != NULL && p1 != NULL && p2 != NULL && p1->_nb_vertices == p2->_nb_vertices)
    {
        for (int i = 0; i < p1->_nb_vertices + 1; ++i)
        {
            quad q = q_new
            (
                p1->_vertices[i],
                p2->_vertices[i],
                p2->_vertices[i + 1],
                p1->_vertices[i + 1]
            );
            m_add_quad (m, q);
        }
    }
}

void m_revolution (mesh * const m, const polygon * const p1, int nb_slices)
{
    if (m != NULL && p1 != NULL && nb_slices > 0)
    {
        polygon a, b;
        p_copy (p1, & a);
        p_copy (p1, & b);

        double angle = (double) 2.0 * M_PI / nb_slices;
        for (int i = 0; i < nb_slices; ++i)
        {
            p_turn_around_y (& b, angle);
            m_add_slice (m, & a, & b);
            p_copy (& b, & a);
        }
    }
}

void m_perlin_extrude (mesh * const m, const polygon * const p, int nb_slices)
{
    if (m != NULL && p != NULL && nb_slices > 0)
    {
        polygon a, b;
        p_copy (p, & a);
        p_copy (p, & b);

        for (int i = 0; i < nb_slices; ++i)
        {
            vector center = p_center (& b);
            vector noise = prln_vector_noise (center);
            p_translate (& b, noise);
            p_rotate (& b, noise);
            m_add_slice (m, & a, & b);
            p_copy (& b, & a);
        }
    }
}

void m_draw (const mesh * const m)
{
    if (m != NULL)
        for (int i = 0; i < m->_nb_quads; ++i)
            q_draw (& m->_quads[i]);
}
