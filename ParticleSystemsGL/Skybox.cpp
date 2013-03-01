//
//  Skybox.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "Skybox.h"
#include "gl_math.h"


Skybox::Skybox(Vector3D startPosition, GLfloat length, TextureLoader* texture_loader) :
Drawable(startPosition),
m_length(length),
m_texture_loader(texture_loader)
{
    loadTextures();
}

Skybox::~Skybox()
{
    //TODO: Unload textures? - problem if multiple glasscube instances exist
}

void Skybox::update(double delta){
    ;
}

GLfloat Skybox::getLength() const
{
    return m_length;
}

void Skybox::draw(){
    glPushMatrix();
    Drawable::draw();
    
    const GLfloat points[8][3] = {
        {0.0f,     0.0f,    0.0f},       //P0
        {m_length, 0.0f,    0.0f},       //P1
        {m_length, 0.0f,    -m_length},   //P2
        {0.0f,     0.0f,    -m_length},   //P3
        {0.0f,     m_length, 0.0f},      //P4
        {m_length, m_length, 0.0f},      //P5
        {m_length, m_length, -m_length},  //P6
        {0.0f,     m_length, -m_length}   //P7
    };
    
    glEnable(GL_TEXTURE_2D);
    glDisable (GL_DEPTH_TEST);
    
    //Top
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[4][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[5][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[7][0]);
    glEnd();
    
    //Right
    glBindTexture(GL_TEXTURE_2D, m_texture[1]);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[2][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[5][0]);
    glEnd();
    
    
    //Bottom
    glBindTexture(GL_TEXTURE_2D, m_texture[2]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&points[0][0]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&points[2][0]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&points[3][0]);
    glEnd();
    
    
    //Left
    glBindTexture(GL_TEXTURE_2D, m_texture[3]);
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[0][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[3][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[7][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[4][0]);
    glEnd();
    
    //Front
    glBindTexture(GL_TEXTURE_2D, m_texture[4]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[5][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[4][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[0][0]);
    glEnd();
    
    //Back
    glBindTexture(GL_TEXTURE_2D, m_texture[5]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[2][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[7][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[3][0]);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    
}

void Skybox::loadTextures()
{
    //Load all textures of the skybox
    m_texture[0] = m_texture_loader->loadTexture("skybox/skybox_top.png");
    m_texture[1] = m_texture_loader->loadTexture("skybox/skybox_right.png");
    m_texture[2] = m_texture_loader->loadTexture("skybox/skybox_bottom.png");
    m_texture[3] = m_texture_loader->loadTexture("skybox/skybox_left.png");
    m_texture[4] = m_texture_loader->loadTexture("skybox/skybox_front.png");
    m_texture[5] = m_texture_loader->loadTexture("skybox/skybox_back.png");
}
