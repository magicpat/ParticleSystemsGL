//
//  first_try.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Fontain.h"

#include "Window.h"
#include <stdio.h>
#include <math.h>


Fontain::Fontain(Vector3D startPosition, TextureLoader* texture_loader) :
    Drawable(startPosition, true),
    m_texture(texture_loader->loadTexture("star.png")),
    m_radius(1.0f),
    m_texture_loader(texture_loader)
{
    glCreateParticles();
}


Fontain::~Fontain(){
    ;
}

void Fontain::glCreateParticles () {
    int i;
    for (i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i].Xpos = 0;
        m_particles[i].Ypos = 0;
        m_particles[i].Zpos = 0;
        m_particles[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        m_particles[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        m_particles[i].Red = 1;
        m_particles[i].Green = 1;
        m_particles[i].Blue = 1;
        m_particles[i].Scalez = 0.25;
        m_particles[i].Direction = 0;
        m_particles[i].Acceleration = ((((((8 - 5 + 2) * rand() % 11) + 5) - 1 + 1) * rand() % 11) + 1) * 0.02;
        m_particles[i].Deceleration = 0.0025;
    }
}

void Fontain::glUpdateParticles(int delta){
    //TODO: INVOLVE delta
    int i;
    for (i = 1; i < MAX_PARTICLES; i++) {
        
        glColor3f (m_particles[i].Red, m_particles[i].Green, m_particles[i].Blue);
        
        m_particles[i].Ypos = (m_particles[i].Ypos + m_particles[i].Acceleration) - (m_particles[i].Deceleration);
        m_particles[i].Deceleration = m_particles[i].Deceleration + 0.0025;
        
        m_particles[i].Xpos = m_particles[i].Xpos + m_particles[i].Xmov;
        m_particles[i].Zpos = m_particles[i].Zpos + m_particles[i].Zmov;
        
        m_particles[i].Direction = m_particles[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand() % 11) + 1);
        
        if (m_particles[i].Ypos < -5)
        {
            m_particles[i].Xpos = 0;
            m_particles[i].Ypos = 0;
            m_particles[i].Zpos = 0;
            m_particles[i].Red = 1;
            m_particles[i].Green = 1;
            m_particles[i].Blue = 1;
            m_particles[i].Direction = 0;
            m_particles[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
            m_particles[i].Deceleration = 0.0025;
        }
        
    }
}

void Fontain::update(double delta) {
    glUpdateParticles(delta);
}

void Fontain::draw() {
    glPushMatrix();
    
    Drawable::draw();
    
    for (int i = 1; i < MAX_PARTICLES; i++)
    {
        glPushMatrix();
        
        glTranslatef (m_particles[i].Xpos, m_particles[i].Ypos, m_particles[i].Zpos);
        glRotatef (m_particles[i].Direction - 90, 0, 0, 1);
        
        glScalef(m_particles[i].Scalez, m_particles[i].Scalez, m_particles[i].Scalez);
        
        
        //glDisable (GL_DEPTH_TEST);
        
        //printf("distance: %f\n", m_camera_distance.z);
        glEnable (GL_BLEND);
        
        //Some Level-of-Detail
        if(m_camera_distance < 40)
        {
            glEnable(GL_TEXTURE_2D);
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glBindTexture (GL_TEXTURE_2D, m_texture);
            glBegin (GL_QUADS);
            glTexCoord2d (0, 0);
            glVertex3f (-1, -1, 0);
            glTexCoord2d (1, 0);
            glVertex3f (1, -1, 0);
            glTexCoord2d (1, 1);
            glVertex3f (1, 1, 0);
            glTexCoord2d (0, 1);
            glVertex3f (-1, 1, 0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
        }
        else{
            if(m_camera_distance > 70)
            {
                glColor4f(1.0, 1.0, 0.0 ,0.5);
            }
            else
            {
                glColor4f(1.0, 0.0, 0.0, 0.5);
            }
            
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
            //glDisable(GL_CULL_FACE);
            glBegin (GL_QUADS);
            glVertex3f (-1, -1, 0);
            glVertex3f (1, -1, 0);
            glVertex3f (1, 1, 0);
            glVertex3f (-1, 1, 0);
            glEnd();
            //glEnable(GL_CULL_FACE);
        }
        
        glDisable(GL_BLEND);
        glPopMatrix();
        //glEnable(GL_DEPTH_TEST);
    }
    glPopMatrix();
}