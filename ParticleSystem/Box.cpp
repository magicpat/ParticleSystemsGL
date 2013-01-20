//
//  Box.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Box.h"
#include "gl_math.h"


Box::Box(Vector3D startPosition, GLfloat length, GLfloat width, GLfloat height) : Drawable(startPosition),
                                                                                  m_length(length),
                                                                                  m_width(width),
                                                                                  m_height(height)
{
    ;
}

void Box::update(int delta){
    ;
}


void Box::draw(){
    glPushMatrix();
    
    Drawable::draw();
    
    // Turn on wireframe mode
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    
    glBegin(GL_QUADS);
    
    const GLfloat points[8][3] = {
        {0.0f,     0.0f,    0.0f},       //P0
        {m_length, 0.0f,    0.0f},       //P1
        {m_length, 0.0f,    -m_width},   //P2
        {0.0f,     0.0f,    -m_width},   //P3
        {0.0f,     m_height, 0.0f},      //P4
        {m_length, m_height, 0.0f},      //P5
        {m_length, m_height, -m_width},  //P6
        {0.0f,     m_height, -m_width}   //P7
    };

    //Unten
    glColor3f(0.82, 0.41, 0.12);
    glNormal3f(0.0f, -1.0f, 0.0f);
    
    glVertex3fv(&points[0][0]);
    glVertex3fv(&points[1][0]);
    glVertex3fv(&points[2][0]);
    glVertex3fv(&points[3][0]);
    
    //Oben
    glColor3f(0.2f, 0.5f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    glVertex3fv(&points[4][0]);
    glVertex3fv(&points[5][0]);
    glVertex3fv(&points[6][0]);
    glVertex3fv(&points[7][0]);

    //Vorne
    glColor3f(0.73, 0.58, 0.58);
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    glVertex3fv(&points[1][0]);
    glVertex3fv(&points[5][0]);
    glVertex3fv(&points[4][0]);
    glVertex3fv(&points[0][0]);
    
    //Hinten
    glColor3f(1.0, 0.5, 0.82);
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    glVertex3fv(&points[2][0]);
    glVertex3fv(&points[6][0]);
    glVertex3fv(&points[7][0]);
    glVertex3fv(&points[3][0]);
    
    //Links
    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    
    glVertex3fv(&points[0][0]);
    glVertex3fv(&points[3][0]);
    glVertex3fv(&points[7][0]);
    glVertex3fv(&points[4][0]);

    //Rechts
    glColor3f(0, 0, 1);
    glNormal3f(1.0f, 0.0f, 0.0f);
    
    glVertex3fv(&points[1][0]);
    glVertex3fv(&points[2][0]);
    glVertex3fv(&points[6][0]);
    glVertex3fv(&points[5][0]);
    
    
    glEnd();
    
    // Turn off wireframe mode
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    
    glPopMatrix();
    
}