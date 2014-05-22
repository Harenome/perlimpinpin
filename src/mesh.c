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

quad q_new (point a, point b, point c, point d)
{
    return (quad) { ._vertices = { a, b, c, d } };
}

void q_print (const quad * const q, const char * const message)
{
    #ifdef __ENABLE_DEBUG
        if (message != NULL)
            fprintf (stderr, "%s:\n", message);
        if (q != NULL)
            for (int i = 0; i < 4; ++i)
                v_print (q->_vertices[i], NULL);
    #endif
}

mesh * m_new (void)
{
    mesh * const m = malloc (sizeof * m);

    if (m != NULL)
    {
        m->_nb_quads = 0;
        m->_is_filled = 0;
    }
    else
    {
        perror ("malloc");
    }

    return m;
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
