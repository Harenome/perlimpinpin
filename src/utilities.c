/**
 * \file utilities.c
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
#include "utilities.h"

static double _d_epsilon = D_DEFAULT_EPSILON;

void d_approximate_epsilon (void)
{
    /* Voir https://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C */
    double new_eps;

    for (new_eps = 1.0; (double) (1.0 + (new_eps / 2.0)) != 1.0; new_eps /= 2.0)
        ;

    _d_epsilon = new_eps;
}

double d_epsilon (void)
{
    return _d_epsilon;
}

bool d_equals (double a, double b)
{
    return fabs (a - b) < _d_epsilon;
}
bool d_is_zero (double d)
{
    return d_equals (d, 0.0);
}

double d_square (double d)
{
    return d * d;
}

double d_det (double a, double b, double i, double j)
{
    /* Déterminant:
     *  | a   i |
     *  | b   j |
     */
    return a * j - b * i;
}
