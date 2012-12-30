//
//  Keyboard.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Keyboard__
#define __ParticleSystem__Keyboard__

#include "Camera.h"
#include "Game.h"
#include "Window.h"

#define ROTATION_SPEED 2.0f
#define TRANSLATION_SPEED 0.05f

class Keyboard {
public:
    Keyboard(Game* game, Camera* camera, Window* window);
    void listen();
    
private:
    static void keyPressed(unsigned char key, int x, int y);
	static void specialKeyPressed(int key, int x, int y);
    
    static Camera* m_camera;
    static Game* m_game;
    static Window* m_window;
    
};
#endif
