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
#include "GlassCube.h"
#include "gl_math.h"
#include "3DS.h"

Game::Game(Camera* camera, TextureLoader* texture_loader) : m_camera(camera), m_texture_loader(texture_loader){
    ;
}

Game::~Game()
{

}

void Game::init(){
    float roomLength = 50.0;
    float roomWidth = 50.0;
    float roomHeight = 50.0;
    
    Vector3D roomCenter = Vector3D(roomLength / 2, roomHeight / 2, -roomWidth / 2);
    
    m_camera->setPosition(Vector3D(roomCenter.x, roomCenter.y + 7.0, roomCenter.z + 10.0));
    
    Drawable* fontain = new Fontain(roomCenter, m_texture_loader);
    Drawable* obstacle = new GlassCube(roomCenter, 1.0, m_texture_loader);
    Drawable* room = new Box(Vector3D(0.0f, 0.0f, 0.0f), roomLength, roomWidth, roomHeight);
    
    //3DS TEST
    /*
     m_camera->setPosition(Vector3D(0.0, 0.0, 0.0));
     Drawable* village = new Model();
    dynamic_cast<Model*>(village)->loadFile("/Users/ps/XCodeProjects/ParticleSystem/ParticleSystem/resources/pyramid.3ds");
    this->addDrawable(village);
     */
    //END 3DS TEST
    
    this->addDrawable(fontain);
    
    this->addDrawable(obstacle);
    this->addDrawable(new GlassCube(Vector3D(roomCenter.x, roomCenter.y, roomCenter.z + 2.0), 2.0, m_texture_loader));
    this->addDrawable(room);
}

void Game::start(){
    this->init();
}

void Game::update(int delta){
    for(std::vector<Drawable*>::size_type i = 0; i != this->m_drawables.size(); i++) {
        Drawable* d = m_drawables[i];
        d->update(delta);
        
        //Recalculate distance to camera
        d->setCameraDistance(d->getPosition() - m_camera->getPosition());
    }
    
    //Update distances of Camera
    std::sort(m_drawables.begin(), m_drawables.end(), Drawable::AscendingCameraDistanceSort());
}

void Game::draw(){
    //Set to MODELVIEW to ensure the right rendering mode
    glMatrixMode(GL_MODELVIEW);
    
    for(std::vector<Drawable*>::size_type i = 0; i != m_drawables.size(); i++) {
        m_drawables[i]->draw();
    }

}

void Game::addDrawable(Drawable* d){
    this->m_drawables.push_back(d);
}

