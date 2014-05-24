/**
 * \file window_common.c
 * \brief Window common.
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
#include "window_common.h"

static polygon _POLYGON;
static mesh _MESH;

void window_common_init (void)
{
    p_init (& _POLYGON);
    m_init (& _MESH);

    p_add_vertex (& _POLYGON, v_new (0.0, -0.5, 0.0));
    p_add_vertex (& _POLYGON, v_new (1.0, 0.0, 0.0));
    p_add_vertex (& _POLYGON, v_new (0.0, 0.5, 0.0));
    p_add_vertex (& _POLYGON, v_new (0.5, 0.0, 0.0));
    p_close (& _POLYGON);
    m_revolution (& _MESH, & _POLYGON, 100);
    m_print (& _MESH, NULL);
}

const polygon * const common_polygon (void)
{
    return & _POLYGON;
}

const mesh * const common_mesh (void)
{
    return & _MESH;
}

void common_polygon_add_vertex (point v)
{
    p_add_vertex (& _POLYGON, v);
}

void common_polygon_close (void)
{
    p_close (& _POLYGON);
}

void common_mesh_perlin_extrude (int slices)
{
    m_perlin_extrude (& _MESH, & _POLYGON, slices);
}

void draw_common_polygon (void)
{
    p_draw (& _POLYGON, WIDTH, HEIGHT);
}

void draw_common_mesh (void)
{
    m_draw (& _MESH);
}
