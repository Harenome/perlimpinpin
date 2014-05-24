/**
 * \file quad.h
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
#ifndef _QUAD_H_
#define _QUAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"

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
 * \relates quad
 */
void q_print (const quad * const q, const char * const message);

/**
 * \brief Dessiner un quadrilatère.
 * \param q Quadrilatère
 * \relates quad
 */
void q_draw (const quad * const q);

#endif /* _QUAD_H_ */
