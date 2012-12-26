//
//  LUtil.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//
#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

/*
 Pre Condition:
 -A valid OpenGL context
 Post Condition:
 -Initializes matrices and clear color
 -Reports to console if there was an OpenGL error
 -Returns false if there was an error in initialization
 Side Effects:
 -Projection matrix is set to identity matrix
 -Modelview matrix is set to identity matrix
 -Matrix mode is set to modelview
 -Clear color is set to black
 */
bool initGL();

/*
 Pre Condition:
 -None
 Post Condition:
 -Does per frame logic
 Side Effects:
 -None
 */
void update();

/*
 Pre Condition:
 -A valid OpenGL context
 -Active modelview matrix
 Post Condition:
 -Renders the scene
 Side Effects:
 -Clears the color buffer
 -Swaps the front/back buffer
 */
void render();

#endif
