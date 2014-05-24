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
#include <stdbool.h>
#include <math.h>

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
 * \param f \c double à comparer.
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
 * \param f \c double.
 * \return Carré.
 */
double d_square (double d);
