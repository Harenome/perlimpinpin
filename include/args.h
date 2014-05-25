/**
 * \file args.h
 * \brief Args.
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
#ifndef _ARGS_H_
#define _ARGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sysexits.h>

static const int VERSION_MAJOR = 0;
static const int VERSION_MINOR = 3;
static const int VERSION_PATCH = 0;

/**
 * \brief Parser les arguments de la ligne de commande.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 * \return Code de sortie.
 */
int stupid_parse (int argc, char ** argv);

#endif /* _ARGS_H_ */
