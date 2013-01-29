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
    Drawable(startPosition),
    m_length(length),
    m_texture_loader(texture_loader)
{
    loadTextures();
}

void GlassCube::update(int delta){
    ;
}


void GlassCube::draw(){
    glPushMatrix();
    Drawable::draw();
    /*
    glTranslatef(m_position.x, m_position.y, m_position.z); //Move to origin
    
    glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
    glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
    glRotatef(m_rotation.z , 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 0.0f);
    
    
     glTranslatef(m_position.x, m_position.y, m_position.z); //Move back to the actual position
     glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
     glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
     glRotatef(m_rotation.z , 0.0, 0.0, 1.0);
     glTranslatef(-m_width/2, 0, 0); //Move to origin
     */
    
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
    
    glPopMatrix();
    
}

void GlassCube::loadTextures()
{
    //Loads the texture and makes it ready for use
    m_texture = m_texture_loader->loadTexture("glass.bmp");
}
