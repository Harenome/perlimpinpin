/**
 * \file window.c
 * \brief Window.
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
#include "window.h"

void init_shade (void)
{
    GLfloat mat_diffuse[] = {1,1,1,1.0};
    GLfloat mat_ambient[] = {0.1,0.1,0.1,0.0};

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glLightfv (GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
    glLightfv (GL_LIGHT0, GL_AMBIENT, mat_ambient);
    glLightfv (GL_LIGHT0, GL_POSITION, p_light);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);
}

void window_init (int argc, char ** argv)
{
    window_common_init ();

    glutInit (& argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("Perlimpinpin");
    glViewport (0, 0, WIDTH, HEIGHT);
    glClearColor (0,0,0,0);

    glutDisplayFunc (display);
    //	glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (special);
    glutMouseFunc (mouse);
    glutIdleFunc (idle);

    p_light[0] = -10.0;
    p_light[1] = 20.0;
    p_light[2] = 0.0;
    p_light[3] = 1.0;

    /* p_aim = v_new (0,0,-2.75); */
}
