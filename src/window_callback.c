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

static int _dim;

static bool _lighting;
static double _x_translation;
static double _y_translation;
static double _horizontal_rotation;
static double _vertical_rotation;
static double _scale;

void callback_init (void)
{
    _dim = DIM2;
    _lighting = false;
    _x_translation = 0.0;
    _y_translation = 0.0;
    _horizontal_rotation = 0.0;
    _vertical_rotation = 0.0;
    _scale = 1.0;
}

static inline void _add_to_value (double * const value, double x)
{
    * value += x;
}

static inline void _angle_increase (double * const value)
{
    _add_to_value (value, ROTATION_STEP);
}

static inline void _angle_decrease (double * const value)
{
    _add_to_value (value, - ROTATION_STEP);
}

static inline void _translation_increase (double * const value)
{
    _add_to_value (value, TRANSLATION_STEP);
}

static inline void _translation_decrease (double * const value)
{
    _add_to_value (value, - TRANSLATION_STEP);
}

static inline void _scale_increase (double * const value)
{
    _add_to_value (value, SCALE_STEP);
}

static inline void _scale_decrease (double * const value)
{
    _add_to_value (value, - SCALE_STEP);
}

static void _go_left (void)
{
    if (is_extruded ())
        _translation_decrease (& _x_translation);
}

static void _go_right (void)
{
    if (is_extruded ())
        _translation_increase (& _x_translation);
}

static void _go_up (void)
{
    if (is_extruded ())
        _translation_increase (& _y_translation);
}

static void _go_down (void)
{
    if (is_extruded ())
        _translation_decrease (& _y_translation);
}

static void _rotate_left (void)
{
    if (is_extruded ())
        _angle_decrease (& _horizontal_rotation);
}

static void _rotate_right (void)
{
    if (is_extruded ())
        _angle_increase (& _horizontal_rotation);
}

static void _rotate_up (void)
{
    if (is_extruded ())
        _angle_increase (& _vertical_rotation);
}

static void _rotate_down (void)
{
    if (is_extruded ())
        _angle_decrease (& _vertical_rotation);
}

static void _zoom_in (void)
{
    if (is_extruded ())
        _scale_increase (& _scale);
}

static void _zoom_out (void)
{
    if (is_extruded ())
        _scale_decrease (& _scale);
}

static void _init_shade (void)
{
    GLfloat mat_diffuse[] = {1, 1, 1, 1.0};
    GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 0.0};
    GLfloat light_0[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_1[] = { 0.0, 0.0, -1.0, 0.0 };

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glLightfv (GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
    glLightfv (GL_LIGHT0, GL_AMBIENT, mat_ambient);
    glLightfv (GL_LIGHT0, GL_POSITION, light_0);

    glLightfv (GL_LIGHT1, GL_DIFFUSE, mat_diffuse);
    glLightfv (GL_LIGHT1, GL_AMBIENT, mat_ambient);
    glLightfv (GL_LIGHT1, GL_POSITION, light_1);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);
    glEnable (GL_DEPTH_TEST);
}

static void _switch_lighting (void)
{
    if (is_extruded ())
    {
        if (_lighting)
            glDisable (GL_LIGHTING);
        else
            _init_shade ();

        _lighting = ! _lighting;
    }
}

void display (void)
{
    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_TRUE);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (_dim == DIM2)
        glOrtho (-1,1,-1,1,-1,1);
    else
        gluPerspective (0, (float) WIDTH/HEIGHT, 1, 100);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glScaled (_scale, _scale, _scale);
    glRotated (_horizontal_rotation, 0, 1, 0);
    glRotated (_vertical_rotation, 1, 0, 0);
    glTranslated (_x_translation, _y_translation, 0.0);

    if (is_extruded ())
        draw_common_mesh ();
    else
        draw_common_polygon ();

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
        case '8':
            _rotate_up ();
            break;
        case '2':
            _rotate_down ();
            break;
        case 'r':
            window_common_init ();
            callback_init ();
            break;
        case 'p':
            common_mesh_perlin_extrude ();
            break;
        case 32:
            /* SPACE */
            _switch_lighting ();
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

void special (int keycode, int x, int y)
{
    switch (keycode)
    {
        case GLUT_KEY_UP:
            debug ("Flèche haut\n");
            _go_up ();
            break;
        case GLUT_KEY_DOWN:
            debug ("Flèche bas\n");
            _go_down ();
            break;
        case GLUT_KEY_LEFT:
            debug ("Flèche gauche\n");
            _go_left ();
            break;
        case GLUT_KEY_RIGHT:
            debug ("Flèche droite\n");
            _go_right ();
            break;
        case GLUT_KEY_PAGE_UP:
            debug ("Flèche avant\n");
            _zoom_in ();
            break;
        case GLUT_KEY_PAGE_DOWN :
            debug ("Flèche arriere\n");
            _zoom_out ();
            break;
        default :
            #ifdef __ENABLE_DEBUG
                fprintf (stderr, "function special : unknown keycode %d\n", keycode);
            #endif
            break;
    }
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
        case 3:
            _zoom_in ();
            break;
        case 4:
            _zoom_out ();
            break;
        case GLUT_RIGHT_BUTTON:
            common_mesh_perlin_extrude ();
            break;
        default:
            break;
    }

    glutPostRedisplay ();
}

void idle (void)
{
    glutPostRedisplay ();
}
