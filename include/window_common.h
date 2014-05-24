/**
 * \file window_common.h
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
#ifndef _WINDOW_COMMON_H_
#define _WINDOW_COMMON_H_

#include "utilities.h"
#include "vector.h"
#include "polygon.h"
#include "mesh.h"

static const int WIDTH = 650;
static const int HEIGHT = 650;

static GLfloat p_light[4];

void window_common_init (void);

bool is_extruded (void);

void common_polygon_add_vertex (point v);
void common_mesh_perlin_extrude (void);

void draw_common_polygon (void);
void draw_common_mesh (void);

#endif /* _WINDOW_COMMON_H_ */
