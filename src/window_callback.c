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

    draw_common_polygon ();
    draw_common_mesh ();

    glutSwapBuffers ();
}

void keyboard (unsigned char keycode, int x, int y)
{
    switch (keycode)
    {
        case '6':
            _rotate_right ();
            break;
        case '4':
            _rotate_left ();
            break;
        case 'r':
            window_common_init ();
            break;
        case 'p':
            common_mesh_perlin_extrude (3);
            break;
        case 27:
            /* ECHAPH */
            exit (0);
            break;
        default:
            break;
    }
    #ifdef __ENABLE_DEBUG
        fprintf(stderr, "Touche frapee : %c (code ascii %d)\n",keycode, keycode);
    #endif

    glutPostRedisplay ();
}

void _debug (const char * const message)
{
    fprintf (stderr, message);
}

void special (int keycode, int x, int y)
{
    int mod = glutGetModifiers ();
    switch (keycode)
    {
        case GLUT_KEY_UP:
            _debug ("Flèche haut\n");
            _go_up ();
            break;
        case GLUT_KEY_DOWN:
            _debug ("Flèche bas\n");
            _go_down ();
            break;
        case GLUT_KEY_LEFT:
            _debug ("Flèche gauche\n");
            _go_left ();
            break;
        case GLUT_KEY_RIGHT:
            _debug ("Flèche droite\n");
            _go_right ();
            break;
        case GLUT_KEY_PAGE_UP:
            _debug ("Flèche avant\n");
            _go_close ();
            break;
        case GLUT_KEY_PAGE_DOWN :
            _debug ("Flèche arriere\n");
            _go_away ();
            break;
        default :
            #ifdef __ENABLE_DEBUG
                fprintf (stderr, "function special : unknown keycode %d\n", keycode);
            #endif
            break;
    }
    if (mod == GLUT_ACTIVE_CTRL)
        glLightfv (GL_LIGHT0, GL_POSITION, p_light);
}

static inline double _mouse_to_double (int v, int v_max)
{
    return (double) v / v_max * 2 - 1.0;
}

static inline double _x_to_double (int x)
{
    return _mouse_to_double (x, WIDTH);
}

static inline double _y_to_double (int y)
{
    return - _mouse_to_double (y, HEIGHT);
}

void mouse (int button, int state, int x, int y)
{
    #ifdef __ENABLE_DEBUG
        fprintf (stderr, "Clic at %d %d \n", x, y);
    #endif

    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                double x_double = _x_to_double (x);
                double y_double = _y_to_double (y);
                vector v = v_new (x_double, y_double, 0.0);
                common_polygon_add_vertex (v);
                #ifdef __ENABLE_DEBUG
                    fprintf (stderr, "Double values: %f %f\n", x_double, y_double);
                #endif
            }
            break;
        case GLUT_MIDDLE_BUTTON:
        case GLUT_RIGHT_BUTTON:
        default:
            break;
    }

    glutPostRedisplay ();
}

void idle (void)
{
    glutPostRedisplay ();
}
