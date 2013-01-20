//
//  Input.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Input.h"
#include <unistd.h>

Camera* Input::m_camera;
Game* Input::m_game;
Window* Input::m_window;
Vector2D Input::m_last_mouse_position(0.0, 0.0);
bool Input::keyboardEnabled = false;
bool Input::mouseEnabled = false;


Input::Input(Game* game, Camera* camera, Window* window){
    if(game == NULL || camera == NULL || window == NULL){
        throw "Game, camera and window must not be null!";
    }
    
    Input::m_camera = camera;
    Input::m_game = game;
    Input::m_window = window;
}

void Input::listen(){
    //Mouse-Movement Delegate
    glutPassiveMotionFunc(&Input::mouseMoved);
    
    //Hide the mouse cursor
    glutSetCursor(GLUT_CURSOR_NONE);
    
    //Keypress Delegates
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(&Input::keyToggled);
    glutSpecialFunc(&Input::specialKeyToggled);
    glutKeyboardUpFunc(&Input::keyToggled);
    glutSpecialUpFunc(&Input::specialKeyToggled);
}

void Input::setKeyboardEnabled(bool enabled)
{
    Input::keyboardEnabled = enabled;
}

void Input::setMouseEnabled(bool enabled)
{
    Input::mouseEnabled = enabled;
}

void Input::keyToggled(unsigned char key, int x, int y) {
    //Let ESC still through to exit the program
    if(!Input::keyboardEnabled && key != KEY_ESC)
        return;
        
    switch(key){
        case KEY_ESC:
            Input::m_window->destroy();
            exit(0);
            break;
        case 'w':
        case KEY_CTRL_W:
            Input::m_camera->toggleMovement(CameraMovement::MOVE_FORWARD);
            break;
        case 's':
        case KEY_CTRL_S:
            Input::m_camera->toggleMovement(CameraMovement::MOVE_BACKWARDS);
            break;
        case 'a':
        case KEY_CTRL_A:
            Input::m_camera->toggleMovement(CameraMovement::MOVE_LEFT);
            break;
        case 'd':
        case KEY_CTRL_D:
            Input::m_camera->toggleMovement(CameraMovement::MOVE_RIGHT);
            break;
        case 'e':
        case KEY_CTRL_E:
            Input::m_camera->toggleMovement(CameraMovement::TURN_RIGHT);
            break;
        case 'q':
        case KEY_CTRL_Q:
            Input::m_camera->toggleMovement(CameraMovement::TURN_LEFT);
            break;
        case KEY_SPACE:
        case KEY_CTRL_SPACE:
            Input::m_camera->toggleMovement(CameraMovement::RISE_UP);
            break;
        
    }
}

void Input::specialKeyToggled(int key, int x, int y ){
    if(!Input::keyboardEnabled)
        return;
    
    switch(key){
        case GLUT_KEY_CTRL_L:
            Input::m_camera->toggleMovement(CameraMovement::LOWER_DOWN);
            break;
        case GLUT_KEY_SHIFT_L:
            Input::m_camera->clearMovement();
            break;
    }
}

void Input::mouseMoved(int x, int y) {
    if(!Input::mouseEnabled){
        return;
    }
    
    //Calculate and add the rotation which will be applied in the next update
    Vector2D rotation(Input::m_last_mouse_position.x - x,
                      Input::m_last_mouse_position.y - y);
    
    if(rotation.x == 0 && rotation.y == 0)
    {
        return;
    }
    
    //Add a rotation
    Input::m_camera->addRotation(rotation);
    
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
    Input::m_last_mouse_position = Vector2D(x,y);
}

