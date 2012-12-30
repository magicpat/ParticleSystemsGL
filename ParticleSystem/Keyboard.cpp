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
}

void Keyboard::keyPressed( unsigned char key, int x, int y ) {
    //usleep(50);
    
    switch(key){
        case 27:
            Keyboard::m_window->destroy();
            exit(0);
            break;
        case 'w':
            //Rotate around X forward
            Keyboard::m_camera->rotateX(ROTATION_SPEED);
            break;
        case 's':
            //Rotate around X backwards
            Keyboard::m_camera->rotateX(-ROTATION_SPEED);
            break;
        case 'a':
            //Rotate around Y left
            Keyboard::m_camera->rotateY(ROTATION_SPEED);
            break;
        case 'd':
            //Rotate around Y right
            Keyboard::m_camera->rotateY(-ROTATION_SPEED);
            break;
        case 'e':
            //SideStep right
            Keyboard::m_camera->yaw(-TRANSLATION_SPEED);
            break;
        case 'q':
            //SideStep left
            Keyboard::m_camera->yaw(TRANSLATION_SPEED);
            break;
    }
    
    //Keyboard::m_game->processKeyboardInput(key);
}

void Keyboard::specialKeyPressed( int key, int x, int y ){
    usleep(20);
    switch(key){
        case GLUT_KEY_UP:
            //move forward
            //Keyboard::m_camera->translate(Vector3D(0.0f, 0.0f, TRANSLATION_SPEED));
            Keyboard::m_camera->forward(TRANSLATION_SPEED);
            break;
			
        case GLUT_KEY_DOWN:
            //move backwards
            //Keyboard::m_camera->translate(Vector3D(0.0f, 0.0f, -TRANSLATION_SPEED));
            Keyboard::m_camera->forward(-TRANSLATION_SPEED);
            break;
            
        case GLUT_KEY_RIGHT:
            //Strafe right
            Keyboard::m_camera->translate(Vector3D(-TRANSLATION_SPEED, 0.0f, 0.0f));
            break;
            
        case GLUT_KEY_LEFT:
            //Strafe left
            Keyboard::m_camera->translate(Vector3D(TRANSLATION_SPEED, 0.0f, 0.0f));
            break;
        
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

