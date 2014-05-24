/**
 * \file window.h
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
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "utilities.h"
#include "vector.h"
#include "polygon.h"
#include "mesh.h"
#include "window_common.h"
#include "window_callback.h"

void window_init (int argc, char ** argv);

#endif /* _WINDOW_H_ */
