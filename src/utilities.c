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
static float _f_epsilon = F_DEFAULT_EPSILON;

void f_approximate_epsilon (void)
{
    /* Voir https://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C */
    float new_eps;

    for (new_eps = 1.0f; (float) (1.0 + (new_eps / 2.0)) != 1.0; new_eps /= 2.0f)
        ;

    _f_epsilon = new_eps;
}

float f_epsilon (void)
{
    return _f_epsilon;
}

bool f_equals (float a, float b)
{
    return fabsf (a - b) < _f_epsilon;
}
bool f_is_zero (float f)
{
    return f_equals (f, 0.0f);
}

float f_square (float f)
{
    return f * f;
}
