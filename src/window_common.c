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

static bool _extruded = false;
static polygon _polygon;
static mesh _mesh;

void window_common_init (void)
{
    _extruded = false;
    p_init (& _polygon);
    m_init (& _mesh);
    p_close (& _polygon);
}

void common_polygon_add_vertex (point v)
{
    if (! _extruded)
        p_add_vertex (& _polygon, v);
}

void common_mesh_perlin_extrude (int slices)
{
    if (! _extruded)
    {
        _extruded = true;
        m_perlin_extrude (& _mesh, & _polygon, slices);
    }
}

void draw_common_polygon (void)
{
    p_draw (& _polygon, WIDTH, HEIGHT);
}

void draw_common_mesh (void)
{
    m_draw (& _mesh);
}
