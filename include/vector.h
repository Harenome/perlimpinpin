
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Vector.h
  \*======================================================*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float x, y, z;
} vector;

vector v_new (float x, float y, float z);

void v_print (vector v, char * message);
vector v_add (vector v1, vector v2);
vector v_substract (vector v1, vector v2);
vector v_multiply (double lambda, vector v);
vector v_cross (vector v1, vector v2);
float v_dot (vector v1, vector v2);
float v_length (vector v);
vector v_unit (vector v);
int v_is_on_the_right (vector m, vector a, vector b);
int v_segments_intersect (vector p1, vector p2, vector q1, vector q2);
int v_ray_intersects_segment (vector m, vector u_ray, vector p1, vector p2);

vector v_turn_around_y (vector p, double angle);
vector v_turn_around_z (vector p, double angle);
vector v_project_on_plane (vector v, vector normal);

double v_decompose (vector p, vector u);
vector v_recompose (double x, double y, double z, vector u, vector v, vector w);
void v_ux_uy_from_uz (vector u_z, vector * u_x, vector * u_y);

#endif // __VECTOR_H__
