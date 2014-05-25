/**
 * \file perlin.h
 * \brief Perlin.
 * \author HABIBI Arash
 * \date May the 29 2013
 */
#ifndef _PERLIN_H_
#define _PERLIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

/**
 * \brief PRLN_000
 */
#define PRLN_000 0

/**
 * \brief PRLN_100
 */
#define PRLN_100 1

/**
 * \brief PRLN_010
 */
#define PRLN_010 2

/**
 * \brief PRLN_110
 */
#define PRLN_110 3

/**
 * \brief PRLN_001
 */
#define PRLN_001 4

/**
 * \brief PRLN_101
 */
#define PRLN_101 5

/**
 * \brief PRLN_011
 */
#define PRLN_011 6

/**
 * \brief PRLN_111
 */
#define PRLN_111 7

/**
 * \brief Bruit de Perlin, scalaire.
 * \param p Vecteur.
 * \return Bruit scalaire.
 */
double prln_scalar_noise (vector p);

/**
 * \brief Bruit de Perlin, vectoriel.
 * \param p Vecteur.
 * \return Bruit vectoriel.
 */
vector prln_vector_noise (vector p);

#endif

