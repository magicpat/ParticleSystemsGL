//
//  Keyboard.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Keyboard.h"
#include <unistd.h>

Camera* Keyboard::m_camera;
Game* Keyboard::m_game;
Window* Keyboard::m_window;
Vector2D Keyboard::m_last_mouse_position(0.0, 0.0);


Keyboard::Keyboard(Game* game, Camera* camera, Window* window){
    if(game == NULL || camera == NULL || window == NULL){
        throw "Game, camera and window must not be null!";
    }
    
    Keyboard::m_camera = camera;
    Keyboard::m_game = game;
    Keyboard::m_window = window;
}

void Keyboard::listen(){
    //Mouse-Movement Delegate
    glutPassiveMotionFunc(&Keyboard::mouseMoved);
    
    //Hide the mouse cursor
    glutSetCursor(GLUT_CURSOR_NONE);
    
    //Keypress Delegates
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(&Keyboard::keyToggled);
    glutSpecialFunc(&Keyboard::specialKeyToggled);
    glutKeyboardUpFunc(&Keyboard::keyToggled);
    glutSpecialUpFunc(&Keyboard::specialKeyToggled);
}

void Keyboard::keyToggled(unsigned char key, int x, int y) {
    switch(key){
        case KEY_ESC:
            Keyboard::m_window->destroy();
            exit(0);
            break;
        case 'w':
        case KEY_CTRL_W:
            Keyboard::m_camera->toggleMovement(CameraMovement::MOVE_FORWARD);
            break;
        case 's':
        case KEY_CTRL_S:
            Keyboard::m_camera->toggleMovement(CameraMovement::MOVE_BACKWARDS);
            break;
        case 'a':
        case KEY_CTRL_A:
            Keyboard::m_camera->toggleMovement(CameraMovement::MOVE_LEFT);
            break;
        case 'd':
        case KEY_CTRL_D:
            Keyboard::m_camera->toggleMovement(CameraMovement::MOVE_RIGHT);
            break;
        case 'e':
        case KEY_CTRL_E:
            Keyboard::m_camera->toggleMovement(CameraMovement::TURN_RIGHT);
            break;
        case 'q':
        case KEY_CTRL_Q:
            Keyboard::m_camera->toggleMovement(CameraMovement::TURN_LEFT);
            break;
        case KEY_SPACE:
            Keyboard::m_camera->toggleMovement(CameraMovement::RISE_UP);
            break;
        
    }
}

void Keyboard::specialKeyToggled(int key, int x, int y ){
    switch(key){
        case GLUT_KEY_CTRL_L:
            Keyboard::m_camera->toggleMovement(CameraMovement::LOWER_DOWN);
            break;
        default:
            return;
    }
}

void Keyboard::mouseMoved(int x, int y) {
    //Calculate and add the rotation which will be applied in the next update
    Vector2D rotation(Keyboard::m_last_mouse_position.x - x,
                      Keyboard::m_last_mouse_position.y - y);
    
    if(rotation.x == 0 && rotation.y == 0)
    {
        return;
    }
    
    //Add a rotation
    Keyboard::m_camera->addRotation(rotation);
    
    int windowX		= glutGet( GLUT_WINDOW_X );
	int windowY		= glutGet( GLUT_WINDOW_Y );
	int screenWidth		= Window::SCREEN_WIDTH;
	int screenHeight	= Window::SCREEN_HEIGHT;
    
    int screenLeft = -windowX;
	int screenTop = -windowY;
	int screenRight = screenWidth - windowX;
	int screenBottom = screenHeight - windowY;
    
	if( x <= screenLeft+10 || (y) <= screenTop+10 || x >= screenRight-10 || y >= screenBottom - 10) {
        x = screenWidth/2;
        y = screenHeight/2;
		glutWarpPointer(x, y);
	}
    
    //Remember last mouse position
    Keyboard::m_last_mouse_position = Vector2D(x,y);
}

