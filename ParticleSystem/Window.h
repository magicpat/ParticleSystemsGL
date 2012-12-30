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
#include "Camera.h"
#include "Game.h"
#include <vector>


class Window{

public:
    //Screen Constants
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    static const int SCREEN_FPS = 60;
    
    //Static methods
    static void render(); //TODO: Should definitaley be a tick-counter here...
    static void reshape(int width, int height);
    
    //Instance methods
    Window(int argc, char* args[], Game* game, Camera* camera);
    bool destroy();
    
private:
    static void run( int val );
    
    //Static variables to be able to access them in the OpenGL-Callbacks, defined above
    static Game* m_game;
    static Camera* m_camera;
    
    //Instance variables
    int m_window;
};

#endif
