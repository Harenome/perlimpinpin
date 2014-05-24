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

#define _MOVE_STEP 0.1

static vector _eye;
static vector _center;
static vector _up;

void callback_init (void)
{
    _eye = v_new (0.0, 0.0, 1.0);
    _center = v_new (0.0, 0.0, 0.0);
    _up = v_new (0.0, 1.0, 0.0);
}

#define _go(direction, op, step) _eye.direction op ## = step; _center.direction op ## = step

static void _go_left (void)
{
    _go (x, +, _MOVE_STEP);
}

static void _go_right (void)
{
    _go (x, -, _MOVE_STEP);
}

static void _go_up (void)
{
    _go (y, -, _MOVE_STEP);
}

static void _go_down (void)
{
    _go (y, +, _MOVE_STEP);
}

static void _go_close (void)
{
    _go (z, +, _MOVE_STEP);
    printf ("%f, %f\n", _eye.z, _center.z);
}

static void _go_away (void)
{
    _go (z, -, _MOVE_STEP);
    printf ("%f, %f\n", _eye.z, _center.z);
}

static void _rotate_left (void)
{
    _up = v_turn_around_z (_up, 10);
}

static void _rotate_right (void)
{
    _up = v_turn_around_z (_up, -10);
}

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

    /* gluLookAt (_eye.x, _eye.y, _eye.z, _center.x, _center.y, _center.z, _up.x, _up.y, _up.z); */
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* draw_common_polygon (); */
    draw_common_mesh ();

    glutSwapBuffers ();
}

void keyboard (unsigned char keycode, int x, int y)
{
    printf("Touche frapee : %c (code ascii %d)\n",keycode, keycode);
    switch (keycode)
    {
        case '6':
            _rotate_right ();
            break;
        case '4':
            _rotate_left ();
            break;
        default:
            break;
    }

    if (keycode == 27) // ECHAP
        exit (0);

    glutPostRedisplay ();
}

void special (int keycode, int x, int y)
{
    int mod = glutGetModifiers ();
    switch (keycode)
    {
        case GLUT_KEY_UP        : printf("Flèche haut\n"); _go_up (); break;
        case GLUT_KEY_DOWN      : printf("Flèche bas\n"); _go_down (); break;
        case GLUT_KEY_LEFT      : printf("Flèche gauche\n"); _go_left (); break;
        case GLUT_KEY_RIGHT     : printf("Flèche droite\n"); _go_right (); break;
        case GLUT_KEY_PAGE_UP   : printf("Flèche avant\n"); _go_close (); break;
        case GLUT_KEY_PAGE_DOWN : printf("Flèche arriere\n"); _go_away (); break;
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
