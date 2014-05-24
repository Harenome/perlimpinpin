/**
 * \file quad.c
 * \brief Quad.
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
#include "quad.h"

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

void q_draw (const quad * const q)
{
    glBegin (GL_POLYGON);

    for (int i = 0; i < 4; ++i)
    {
        vector v = q->_vertices[i];
        glVertex3d (v.x, v.y, v.z);
    }

    glEnd ();
}
