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

void display (void);

void keyboard (unsigned char keycode, int x, int y);

void special (int keycode, int x, int y);

void mouse (int button, int state, int x, int y);

void idle (void);

#endif /* _WINDOW_CALLBACK_H_ */
