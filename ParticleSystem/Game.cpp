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
#include "GlassCube.h"
#include "Earth.h"
#include "Spaceship.h"
#include "gl_math.h"
#include "3DS.h"

Game::Game(Camera* camera, TextureLoader* texture_loader) : m_camera(camera), m_texture_loader(texture_loader){
    ;
}

Game::~Game()
{
    for(std::vector<Drawable*>::size_type i = 0; i != this->m_drawables.size(); i++) {
        delete m_drawables[i];
    }
}

void Game::init(){
    std::string texture_directory = m_texture_loader->getTextureDirectory();
    
    float roomLength = 800.0;
    
    Vector3D roomCenter = Vector3D(roomLength / 2, roomLength / 2, -roomLength / 2);
    
    m_camera->setPosition(Vector3D(roomCenter.x, roomCenter.y + 7.0, roomCenter.z));
    m_camera->setDirection(Vector3D(0.0,0.0,1.0));
    
    //Create the spaceship model
    Model* spaceship = new Spaceship(m_texture_loader);
    
    //No need to translate because the ship follows the camera
    spaceship->translate(Vector3D(roomCenter.x, roomCenter.y - 20, roomCenter.z + 100));
    spaceship->rotate(Vector3D(250,0,0));
    spaceship->scale(0.05);
    
    addDrawable(spaceship);
    
    m_camera->lookAt(spaceship);
    //Create the earth model
    Model* earth = new Earth(m_texture_loader);
    
    earth->translate(Vector3D(roomCenter.x, roomCenter.y, roomCenter.z));
    earth->scale(0.3);
    addDrawable(earth);
    //earth->disableLights();
    
    //Create the drawable objects
    Drawable* fontain = new Fontain(Vector3D(roomCenter.x+5, roomCenter.y+5, roomCenter.z-7), m_texture_loader);
    
    Drawable* glasscube_big = new GlassCube(roomCenter, 5.0, m_texture_loader);
    Drawable* glasscube_small = new GlassCube(Vector3D(roomCenter.x, roomCenter.y + 2, roomCenter.z + 4.0), 2.0, m_texture_loader);
    
    addDrawable(fontain);
    addDrawable(glasscube_big);
    addDrawable(glasscube_small);
    
    //Create the space
    m_skybox = new Skybox(Vector3D(0.0, 0.0, 0.0), roomLength, m_texture_loader);
}

void Game::start(){
    this->init();
}

void Game::update(double delta){
    for(std::vector<Drawable*>::size_type i = 0; i != this->m_drawables.size(); i++) {
        Drawable* d = m_drawables[i];
        d->update(delta);
        
        //Recalculate distance to camera
        d->setCameraDistance(abs((d->getPosition() - m_camera->getPosition()).length()));
    }
    
    //Update distances of Camera
    std::sort(m_drawables.begin(), m_drawables.end(), Drawable::AscendingCameraDistanceSort());
    
    //Reposition the skybox for "infinity effect"
    centerSkybox();
}

void Game::draw(){
    //Set to MODELVIEW to ensure the right rendering mode
    glMatrixMode(GL_MODELVIEW);
    
    m_skybox->draw();
    for(std::vector<Drawable*>::size_type i = 0; i != m_drawables.size(); i++) {
        m_drawables[i]->draw();
    }

}

void Game::addDrawable(Drawable* d){
    this->m_drawables.push_back(d);
}

void Game::centerSkybox()
{
    static const GLfloat length = m_skybox->getLength();
    Vector3D new_space_position = m_camera->getPosition();

    new_space_position.x -= length/2;
    new_space_position.y -= length/2;
    new_space_position.z += length/2;
    
    m_skybox->setPosition(new_space_position);
}


