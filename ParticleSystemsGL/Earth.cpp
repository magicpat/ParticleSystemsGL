//
//  Earth.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "Earth.h"
#include <string>

Earth::Earth(TextureLoader* texture_loader) : Model(texture_loader)
{
    std::string texture_directory = m_texture_loader->getTextureDirectory();
    loadFile((texture_directory + "/earth/earth.3ds").c_str());
    disableLights();
}

void Earth::update(double delta)
{
    rotate(Vector3D(0.0, 10.0 * delta, 0.0));
}

void Earth::draw()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    
    //glPushMatrix();
    glTranslatef(m_position.x, m_position.y, m_position.z); //Move back to the actual position
    glScalef(m_scalefactor, m_scalefactor, m_scalefactor);
    glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
    glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
    glTranslatef(m_position.x - 200, 0.0f, 0.0f); //Move to origin
    //glPopMatrix();
    
    renderModel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}