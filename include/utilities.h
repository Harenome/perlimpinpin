/**
 * \file utilities.h
 * \brief Utilities.
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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* C99 VS. GNU C99 :
 * PI a été retiré du C99...
 * Mais est toujours présent dans le dialecte GNU du C99.
 */
#ifdef __STRICT_ANSI__
    /* Test juste sur __STRICT_ANSI__, le reste du code est de toutes
     * façons prévu pour C99... */
    # define M_PI		3.14159265358979323846
#endif

/**
 * \brief Epsilon par défaut pour les \c double.
 */
#define D_DEFAULT_EPSILON 1.0e-5

/**
 * \brief Approximer l'epsilon machine pour les \c double.
 */
void d_approximate_epsilon (void);

/**
 * \brief Obtenir l'epsilon couramment utilisé pour les \c double.
 */
double d_epsilon (void);

/**
 * \brief Déterminer si un \c double est égal (à l'epsilon près) à 0.
 * \param d \c double à comparer.
 * \retval true si le \c double est égal à 0.
 * \retval false sinon.
 */
bool d_is_zero (double d);

/**
 * \brief Déterminer si deux \c double sont égaux (à l'epsilon près).
 * \param a \c double à comparer.
 * \param b \c double à comparer.
 * \retval true si les \c double sont égaux.
 * \retval false sinon.
 */
bool d_equals (double a, double b);

/**
 * \brief Obtenir le carré d'un \c double.
 * \param d \c double.
 * \return Carré.
 */
double d_square (double d);

/**
 * \brief Obtenir le déterminant de (\c a, \c b) et (\c i, \c j).
 * \param a \c a.
 * \param b \c b.
 * \param i \c i.
 * \param j \c j.
 * \return Déterminant (\c a * \c j - \c b * \c i).
 */
double d_det (double a, double b, double i, double j);

/**
 * \brief Afficher un message, si le mode debug est actif, sur la sortie d'erreur.
 * \param message Message.
 */
void debug (const char * const message);
