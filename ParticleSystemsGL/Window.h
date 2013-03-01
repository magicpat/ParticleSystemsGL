//
//  Window.h
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
#include "HUD.h"
#include <vector>

#define MAXIMUM_FRAME_RATE 120
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)

class Window{

public:
    //Screen Constants
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    static const int SCREEN_FPS = 60;
    
    //Static methods
    static void reshape(int width, int height);
    
    //Instance methods
    Window(int argc, char* args[], Game* game, Camera* camera, HUD* hud);
    bool destroy();
    
private:
    static void display();
    static void run(int val);
    
    //Static variables to be able to access them in the OpenGL-Callbacks, defined above
    static Game* m_game;
    static Camera* m_camera;
    static HUD* m_hud;
    
    //Instance variables
    int m_window;
};

#endif
