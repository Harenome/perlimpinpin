
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Mesh.h
\*======================================================*/

#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"
#include "polygon.h"
#include "perlin.h"

#define M_MAX_QUADS 5000

typedef struct
{
    vector _vertices[4];
} quad;

quad q_new (vector v1, vector v2, vector v3, vector v4);

//--------------------------------------------

typedef struct
{
    int _nb_quads;
    quad _quads[M_MAX_QUADS];
    int _is_filled;
    // int _is_smooth;
} mesh;

mesh * m_new (void);
void m_print (mesh * p, char * message);

void m_add_quad (mesh * p, quad q);
void m_add_slice (mesh * p, polygon * p1, polygon * p2);
void m_revolution (mesh * p, polygon * p1, int nb_slices);
void m_perlin_extrude (mesh * qm, polygon * p, int nb_slices);

void m_draw (mesh * p);

#endif // _MESH_H_
