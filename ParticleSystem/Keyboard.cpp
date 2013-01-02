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
int Keyboard::m_last_mouse_x = 0;
int Keyboard::m_last_mouse_y = 0;


Keyboard::Keyboard(Game* game, Camera* camera, Window* window){
    if(game == NULL || camera == NULL || window == NULL){
        throw "Game, camera and window must not be null!";
    }
    
    Keyboard::m_camera = camera;
    Keyboard::m_game = game;
    Keyboard::m_window = window;
}

void Keyboard::listen(){
    glutKeyboardFunc(&Keyboard::keyPressed);
    glutSpecialFunc(&Keyboard::specialKeyPressed);
    glutPassiveMotionFunc(&Keyboard::mouseMoved);
}

void Keyboard::keyPressed( unsigned char key, int x, int y ) {
    //usleep(50);
    
    switch(key){
        case 27:
            Keyboard::m_window->destroy();
            exit(0);
            break;
        case 'w':
            //Move forward
            Keyboard::m_camera->forward(0.1);
            break;
        case 's':
            //Move backwards
            Keyboard::m_camera->forward(-0.1);
            break;
        case 'a':
            //Strafe left
            Keyboard::m_camera->sideStep(-0.1);
            break;
        case 'd':
            //Rotate around Y right
            Keyboard::m_camera->sideStep(0.1);
            break;
    }
    
    //Keyboard::m_game->processKeyboardInput(key);
}

void Keyboard::specialKeyPressed( int key, int x, int y ){
    usleep(20);
    switch(key){        
        case GLUT_KEY_PAGE_UP:
            Keyboard::m_camera->translate(Vector3D(0.0f,TRANSLATION_SPEED, 0.0f));
            break;
        case GLUT_KEY_PAGE_DOWN:
            Keyboard::m_camera->translate(Vector3D(0.0f,-TRANSLATION_SPEED, 0.0f));
            break;
        default:
            return;
    }
}

void Keyboard::mouseMoved(int x, int y) {
    int diffX= x - Keyboard::m_last_mouse_x;
    int diffY= y - Keyboard::m_last_mouse_y;
    
    Keyboard::m_last_mouse_x = x; 
    Keyboard::m_last_mouse_y = y;
    
    Keyboard::m_camera->yaw(diffX);
    //Keyboard::m_camera->pitch(diffY);
    
    //Keyboard::m_camera->rotate(Vector3D(diffY, diffX, 0.0));
}

