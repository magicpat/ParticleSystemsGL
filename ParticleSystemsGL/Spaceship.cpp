//
//  Spaceship.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "Spaceship.h"

Spaceship::Spaceship(TextureLoader* texture_loader) : Spaceship(texture_loader, NULL)
{
    ;
}

Spaceship::Spaceship(TextureLoader* texture_loader, Camera* camera) : Model(texture_loader), m_camera(camera)
{
    std::string texture_directory = m_texture_loader->getTextureDirectory();
    loadFile((texture_directory + "/spaceship/spaceship.3ds").c_str());
}

void Spaceship::draw()
{
    if(m_camera)
    {
        Vector3D camera_position = m_camera->getPosition();
        
        m_position = camera_position;
        m_position.x += 10;
        m_position.y -= 10;
        m_position.z -= -100;
    }
    
    Model::draw();
}