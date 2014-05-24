/**
 * \file window_callback.c
 * \brief Window callback.
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
#include "window_callback.h"

#define DIM2 0
#define DIM3 1
static int dim = DIM2;

void display (void)
{
    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_TRUE);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (dim == DIM2)
        glOrtho (-1,1,-1,1,-1,1);
    else
        gluPerspective (40, (float) WIDTH/HEIGHT, 1, 100);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* p_draw (& p, width, height); */
    draw_common_mesh ();

    glutSwapBuffers ();
}

void keyboard (unsigned char keycode, int x, int y)
{
    // printf("Touche frapee : %c (code ascii %d)\n",keycode, keycode);

    if (keycode == 27) // ECHAP
        exit (0);

    glutPostRedisplay ();
}

void special (int keycode, int x, int y)
{
    int mod = glutGetModifiers ();
    switch (keycode)
    {
        case GLUT_KEY_UP        : printf("Flèche haut\n"); break;
        case GLUT_KEY_DOWN      : printf("Flèche bas\n"); break;
        case GLUT_KEY_LEFT      : printf("Flèche gauche\n"); break;
        case GLUT_KEY_RIGHT     : printf("Flèche droite\n"); break;
        case GLUT_KEY_PAGE_UP   : printf("Flèche avant\n"); break;
        case GLUT_KEY_PAGE_DOWN : printf("Flèche arriere\n"); break;
        default : fprintf(stderr,"function special : unknown keycode %d\n",keycode); break;
    }
    if (mod == GLUT_ACTIVE_CTRL)
        glLightfv (GL_LIGHT0, GL_POSITION, p_light);
}

void mouse (int button, int state, int x, int y)
{
    printf ("Clic at %d %d \n",x,y);

    glutPostRedisplay ();
}

void idle (void)
{
    glutPostRedisplay ();
}
