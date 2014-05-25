/**
 * \file window_callback.h
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
#ifndef _WINDOW_CALLBACK_H_
#define _WINDOW_CALLBACK_H_

#include "utilities.h"
#include "vector.h"
#include "polygon.h"
#include "mesh.h"
#include "window_common.h"

/**
 * \brief DIM2
 */
static const int DIM2 = 0;

/**
 * \brief DIM3
 */
static const int DIM3 = 1;

/**
 * \brief Pas de translation.
 */
static const double TRANSLATION_STEP = 0.5;

/**
 * \brief Pas de rotation.
 */
static const double ROTATION_STEP = 10;

/**
 * \brief Pas de zoom.
 */
static const double SCALE_STEP = 0.1;

/**
 * \brief Initialiser le nécessaire pour les fonctions de callback.
 */
void callback_init (void);

/**
 * \brief Fonction d'affichage.
 */
void display (void);

/**
 * \brief Gestion du clavier.
 * \param keycode Touche.
 * \param x X.
 * \param y Y.
 */
void keyboard (unsigned char keycode, int x, int y);

/**
 * \brief Touches spéciales.
 * \param keycode Touche.
 * \param x X.
 * \param y Y.
 */
void special (int keycode, int x, int y);

/**
 * \brief Gestion de la souris.
 * \param button Bouton.
 * \param state État.
 * \param x X.
 * \param y Y.
 */
void mouse (int button, int state, int x, int y);

/**
 * \brief Fonction d'attente.
 */
void idle (void);

#endif /* _WINDOW_CALLBACK_H_ */
