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
#include "Drawable.h"
#include <vector>


class RenderManager{
    
    
public:
    //Screen Constants
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    static const int SCREEN_FPS = 60;
    
    
    
    //Static methods
    static void update();
    static void render();
    static void reshape(int width, int height);
    
    
    
    
    //Non-Static methods
    RenderManager();

    bool init(int argc, char* args[]);
    void addDrawable(Drawable* d);
    
    
    
    
private:
    static void run( int val );
    static std::vector<Drawable*> m_drawables;
    int m_window;
    
};

#endif
