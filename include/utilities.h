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
 * \brief Epsilon par défaut pour les \c float.
 */
#define F_DEFAULT_EPSILON 1.0e-5

/**
 * \brief Approximer l'epsilon machine pour les \c float.
 */
void f_approximate_epsilon (void);

/**
 * \brief Obtenir l'epsilon couramment utilisé pour les \c float.
 */
float f_epsilon (void);

/**
 * \brief Déterminer si un \c float est égal (à l'epsilon près) à 0.
 * \param f \c float à comparer.
 * \retval true si le \c float est égal à 0.
 * \retval false sinon.
 */
bool f_is_zero (float f);

/**
 * \brief Déterminer si deux \c float sont égaux (à l'epsilon près).
 * \param a \c float à comparer.
 * \param b \c float à comparer.
 * \retval true si les \c float sont égaux.
 * \retval false sinon.
 */
bool f_equals (float a, float b);

/**
 * \brief Obtenir le carré d'un \c float.
 * \param f \c float.
 * \return Carré.
 */
float f_square (float f);
