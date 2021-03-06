/**
 * \file polygon.h
 * \brief Polygon.
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
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "utilities.h"
#include "vector.h"

/**
 * \brief Maximum de points par polygone.
 */
#define P_MAX_VERTICES 1000

/**
 * \brief Polygone.
 */
typedef struct
{
    int _nb_vertices;                   /**<- Nombre de sommets. */
    point _vertices[P_MAX_VERTICES];    /**<- Sommets. */
    bool _is_closed;                    /**<- Fermeture. */
    bool _is_filled;                    /**<- Remplissage. */
    bool _is_convex;                    /**<- Convexité. */
} polygon;

/**
 * \brief Créer un nouveau polygone.
 * \return (pointeur vers) Nouveau polygone.
 * \relatesalso polygon
 */
polygon * p_new (void);

/**
 * \brief Initialiser un polygone.
 * \param p Polygone.
 */
void p_init (polygon * const p);

/**
 * \brief Copier un polygone dans un autre.
 * \param[in] original Polygone original.
 * \param[in,out] copy Destination de la copie.
 * \relatesalso polygon
 * \pre copy a été préalablement alloué.
 */
void p_copy (const polygon * const original, polygon * const copy);

/**
 * \brief Ajouter, si possible, un sommet au polygone.
 * \param p Polygone.
 * \param v Sommet.
 * \relatesalso polygon
 */
void p_add_vertex (polygon * const p, point v);

/**
 * \brief Retirer le dernier sommet, s'il y a des sommets.
 * \param p Polygone.
 * \relatesalso polygon
 */
void p_remove_last_vertex (polygon * const p);

/**
 * \brief Afficher un polygone.
 * \param p Polygone.
 * \param message Message.
 * \relatesalso polygon
 */
void p_print (const polygon * const p, const char * const message);

/**
 * \brief Dessiner un polygone.
 * \param p Polygone.
 * \param width Largeur.
 * \param height Hauteur.
 * \relatesalso polygon
 */
void p_draw (const polygon * const p, int width, int height);

/**
 * \brief Fermer un polygone.
 * \param p Polygone.
 * \pre Le polygone a au moins 3 sommets.
 * \warning Le polygone ne sera pas fermé s'il possède moins de 3 sommets.
 */
void p_close (polygon * const p);

/**
 * \brief Déterminer si un polygone est fermé.
 * \param p Polygone.
 * \retval true si le polygone est fermé.
 * \retval false sinon.
 * \relatesalso polygon
 */
bool p_is_closed (const polygon * const p);

/**
 * \brief Déterminer si un polygone est rempli.
 * \param p Polygone.
 * \retval true si le polygone est rempli.
 * \retval false sinon.
 * \relatesalso polygon
 */
bool p_is_filled (const polygon * const p);

/**
 * \brief Déterminer si un polygone est convexe.
 * \param p Polygone.
 * \retval true si le polygone est convexe.
 * \retval false sinon.
 * \relatesalso polygon
 */
bool p_is_convex (const polygon * const p);

/**
 * \brief Déterminer si un point est à la gauche de tous les côtés d'un polygone.
 * \param p Polygone.
 * \param m Point.
 * \retval true si oui.
 * \retval false sinon.
 * \relatesalso polygon
 */
bool p_is_on_the_left_of_all_edges (const polygon * const p, point m);

/**
 * \brief Obtenir le nombre de côtés intersectés par une demi-droite.
 * \param p Polygone.
 * \param m Origine de la demi-droite.
 * \param u_ray Vecteur directeur de la demi-droite.
 * \return Nombre de côtés intersectés.
 * \relatesalso polygon
 */
int p_nb_edges_intersected_by_ray (const polygon * const p, point m, vector u_ray);

/**
 * \brief Déterminer si un point est à l'interieur d'un polygone.
 * \param p Polygone.
 * \param m Point.
 * \retval true si le point est à l'intérieur du polygone.
 * \retval false sinon.
 * \relatesalso polygon
 */
bool p_is_inside (const polygon * const p, point m);

/**
 * \brief Faire tourner un polygone autour de l'axe Y.
 * \param p Polygone.
 * \param angle Angle de rotation.
 * \relatesalso polygon
 */
void p_turn_around_y (polygon * const p, double angle);

/**
 * \brief Obtenir le centre (la moyenne des positions des sommets) d'un polygone plan.
 * \param p Polygone
 * \return centre.
 * \relatesalso polygon
 */
vector p_center (const polygon * const p);

/**
 * \brief Obtenir un vecteur unitaire normal à un polygone plan.
 * \param p Polygone.
 * \return Vecteur unitaire normal au polygone plan.
 * \relatesalso polygon
 */
vector p_normal (const polygon * const p);

/**
 * \brief Mettre à l'échelle un polygone.
 * \param p Polygone.
 * \param factor Facteur de mise à l'échelle.
 * \relatesalso polygon
 */
void p_scale (polygon * const p, double factor);

/**
 * \brief Translater un polygone.
 * \param p Polygone.
 * \param trans Vecteur de translation.
 * \relatesalso polygon
 */
void p_translate (polygon * const p, vector trans);

/**
 * \brief Rotation d'un vecteur autour de son centre afin que son vecteur normal soit égal à \c normal.
 * \param p Polygone.
 * \param normal Vecteur cible.
 * \relatesalso polygon
 */
void p_rotate (polygon * const p, vector normal);

#endif // _POLYGON_H_
