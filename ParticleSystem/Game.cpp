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
#include "Ground.h"
#include "gl_math.h"

Game::Game(Camera* camera) : m_camera(camera){
    
}

void Game::init(){
    m_camera->setPosition(Vector3D(0.0f, 0.1f, 0.0f));
    
    //Drawable* fontain = (Drawable *)new Fontain(Vector3D(0.0f, 0.0f, -10.0f));
    Drawable* ground = (Drawable *)new Ground(Vector3D(0.0f, 0.0f, -0.3f));
    
    //m_camera->lookAt(ground);
    
    //this->addDrawable(fontain);
    this->addDrawable(ground);
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
        //m_drawables[i]->RotateX(1.0f);
        m_drawables[i]->draw();
    }
}

void Game::addDrawable(Drawable* d){
    this->m_drawables.push_back(d);
}

