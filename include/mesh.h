/**
 * \file mesh.h
 * \brief Mesh.
 * \author HABIBI Arash
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date September the 25th 2013 (HABIBI Arash)
 * \date 2014 (RAZANAJATO RANAIVOARIVONY Harenome)
 * \copyright WTFPL version 2
 *
 * \todo m_draw
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
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

/**
 * \brief Nombre maximal de quadrilatères.
 */
#define M_MAX_QUADS 5000

/**
 * \brief Quadrilatère.
 */
typedef struct
{
    point _vertices[4];    /**<- Sommets. */
} quad;

/**
 * \brief Créer un nouveau quadrilatère.
 * \relates quad
 */
quad q_new (point a, point b, point c, point d);

/**
 * \brief Afficher un quadrilatère.
 * \param q Quadrilatère.
 * \param message Message.
 * \relates mesh
 */
void q_print (const quad * const q, const char * const message);

/**
 * \brief Maillage.
 */
typedef struct
{
    int _nb_quads;              /**<- Nombre de quadrilatères. */
    quad _quads[M_MAX_QUADS];   /**<- Quadrilatères. */
    bool _is_filled;            /**<- Remplissage. */
    // int _is_smooth;
} mesh;

/**
 * \brief Créer un nouveau Maillage.
 * \relates mesh
 */
mesh * m_new (void);

/**
 * \brief Afficher un maillage.
 * \param m Maillage.
 * \param message Message.
 * \relates mesh
 */
void m_print (const mesh * const m, const char * const message);

/**
 * \brief Ajouter un quadrilatère.
 * \param m Maillage.
 * \param q Quadrilatère.
 * \relates mesh
 */
void m_add_quad (mesh * const m, quad q);

/**
 * \brief Ajouter une coupe.
 * \param m Maillage.
 * \param p1 Polygone.
 * \param p2 Polygone.
 * \relates mesh
 * \pre p1->_nb_vertices == p2->_nb_vertices
 */
void m_add_slice (mesh * const m, const polygon * const p1, const polygon * const p2);

/**
 * \brief Révolution.
 * \param m Maillage.
 * \param p1 Polygone.
 * \param nb_slices Nombre de coupes.
 * \relates mesh
 */
void m_revolution (mesh * const m, const polygon * const p1, int nb_slices);

/**
 * \brief Extruder selon le bruit de Perlin.
 * \param m Maillage.
 * \param p Polygone.
 * \param nb_slices Nombre de coupes.
 * \relates mesh
 */
void m_perlin_extrude (mesh * const m, const polygon * const p, int nb_slices);

/**
 * \brief Dessiner un maillage.
 * \param m Maillage.
 * \relates mesh
 */
void m_draw (const mesh * const m);

#endif // _MESH_H_
