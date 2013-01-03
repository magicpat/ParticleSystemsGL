//
//  Game.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Game.h"
#include "Fontain.h"
#include "Drawable.h"
#include "Box.h"
#include "gl_math.h"

Game::Game(Camera* camera) : m_camera(camera){
    
}

void Game::init(){
    float roomLength = 50.0;
    float roomWidth = 50.0;
    float roomHeight = 50.0;
    
    Vector3D roomCenter = Vector3D(roomLength / 2, roomHeight / 2, -roomWidth / 2);
    
    m_camera->setPosition(Vector3D(roomCenter.x, roomCenter.y + 7.0, roomCenter.z + 10.0));
    
    //Drawable* fontain = (Drawable *)new Fontain(Vector3D(0.0f, 0.0f, -10.0f));
    Drawable* obstacle = new Box(roomCenter, 1.0, 1.0, 1.0);
    Drawable* room = new Box(Vector3D(0.0f, 0.0f, 0.0f), roomLength, roomWidth, roomHeight);
    
    m_camera->lookAt(obstacle);
    
    //this->addDrawable(fontain);
    this->addDrawable(obstacle);
    this->addDrawable(room);
}

void Game::start(){
    this->init();
}

void Game::processKeyboardInput(const unsigned char c){
    ;
}

void Game::update(){
    for(std::vector<Drawable*>::size_type i = 0; i != this->m_drawables.size(); i++) {
        this->m_drawables[i]->update();
    }
}

void Game::draw(){
    this->update();
    
    //Set to MODELVIEW to ensure the right rendering mode
    glMatrixMode(GL_MODELVIEW);
    
    for(std::vector<Drawable*>::size_type i = 0; i != m_drawables.size(); i++) {
        Drawable* test = m_drawables[i];

        if(i == 0){
            test->rotateY(1.0);
        }
        m_drawables[i]->draw();
    }
}

void Game::addDrawable(Drawable* d){
    this->m_drawables.push_back(d);
}

