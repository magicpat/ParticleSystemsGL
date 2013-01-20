//
//  Input.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Input__
#define __ParticleSystem__Input__

#include "Camera.h"
#include "Game.h"
#include "Window.h"

#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_CTRL_W 23
#define KEY_CTRL_A 1
#define KEY_CTRL_S 19
#define KEY_CTRL_D 4
#define KEY_CTRL_E 5
#define KEY_CTRL_Q 17
#define KEY_CTRL_SPACE 0

class Input {
public:
    Input(Game* game, Camera* camera, Window* window);
    void listen();
    void setKeyboardEnabled(bool enabled);
    void setMouseEnabled(bool enabled);
    
private:
    static void keyToggled(unsigned char key, int x, int y);
	static void specialKeyToggled(int key, int x, int y);
    static void mouseMoved(int x, int y);
    
    //Needed dependencies
    static Camera* m_camera;
    static Game* m_game;
    static Window* m_window;
    
    //For mouse tracking
    static Vector2D m_last_mouse_position;
    
    //For input enabling
    static bool keyboardEnabled;
    static bool mouseEnabled;
};
#endif
