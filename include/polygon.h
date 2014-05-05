
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Polygon.h
  \*======================================================*/

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"

#define P_MAX_VERTICES 1000

typedef struct
{
    int _nb_vertices;
    vector _vertices[P_MAX_VERTICES];
    int _is_closed;
    int _is_filled;
    int _is_convex;
} polygon;

polygon * p_new (void);

void p_copy (polygon * original, polygon * copy);

void p_add_vertex (polygon * p, vector v);
void p_remove_last_vertex (polygon * p);

void p_print (polygon * p, char * message);
void p_draw (polygon * p, int width, int height);

int p_is_convex (polygon * p);
int p_is_on_the_left_of_all_edges (polygon * p, vector m);
int p_nb_edges_intersected_by_ray (polygon * p, vector m, vector u_ray);
int p_is_inside (polygon * p, vector m);
void p_turn_around_y (polygon * p, double radians);

vector p_center (polygon * p);
vector p_normal (polygon * p);
void p_scale (polygon * p, double factor);
void p_translate (polygon * p, vector trans);
void p_rotate (polygon * p, vector normal);

#endif // _POLYGON_H_
