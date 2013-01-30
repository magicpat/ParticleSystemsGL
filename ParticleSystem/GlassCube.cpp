//
//  GlassCube.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 28.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "GlassCube.h"
#include "gl_math.h"


GlassCube::GlassCube(Vector3D startPosition, GLfloat length, TextureLoader* texture_loader) :
    Drawable(startPosition, true),
    m_length(length),
    m_texture_loader(texture_loader)
{
    loadTextures();
}

GlassCube::~GlassCube()
{
    //TODO: Unload textures? - problem if multiple glasscube instances exist
}

void GlassCube::update(double delta){
    ;
}


void GlassCube::draw(){
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
    
    glColor4f(1.0f, 1.0f, 1.0f, 0.5);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable (GL_DEPTH_TEST);
    
    //glDisable(GL_CULL_FACE);
    
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_QUADS);
        //Unten
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&points[0][0]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&points[2][0]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&points[3][0]);
        
        //Oben
        glNormal3f(0.0f, 1.0f, 0.0f);
        
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[4][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[5][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[7][0]);
        
        //Vorne
        glNormal3f(0.0f, 0.0f, 1.0f);
        
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[5][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[4][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[0][0]);
        
        //Hinten
        glNormal3f(0.0f, 0.0f, -1.0f);
        
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[2][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[7][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[3][0]);
        
        //Links
        glNormal3f(-1.0f, 0.0f, 0.0f);
        
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[0][0]);
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[3][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[7][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[4][0]);
        
        //Rechts
        glNormal3f(1.0f, 0.0f, 0.0f);
        
        glTexCoord2f(1.0f, 0.0f);glVertex3fv(&points[1][0]);
        glTexCoord2f(1.0f, 1.0f);glVertex3fv(&points[2][0]);
        glTexCoord2f(0.0f, 1.0f);glVertex3fv(&points[6][0]);
        glTexCoord2f(0.0f, 0.0f);glVertex3fv(&points[5][0]);
    
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glPopMatrix();
    
}

void GlassCube::loadTextures()
{
    //Loads the texture and makes it ready for use
    m_texture = m_texture_loader->loadTexture("glass.bmp");
    
}
