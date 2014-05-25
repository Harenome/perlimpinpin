/**
 * \file main.c
 * \brief Main
 * \author HABIBI Arash
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date September the 25th 2013 (HABIBI Arash)
 * \date 2014 (RAZANAJATO RANAIVOARIVONY Harenome)
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"
#include "polygon.h"
#include "mesh.h"
#include "window.h"

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 * \retval 0
 */
int main (int argc, char ** argv)
{
    callback_init ();
    window_init (argc, argv);

    glutMainLoop ();

    return 0;
}
