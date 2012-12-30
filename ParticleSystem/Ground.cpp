//
//  Ground.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Ground.h"
#include "gl_math.h"


Ground::Ground() : Drawable(){
    
}

Ground::Ground(Vector3D startPosition) : Drawable(startPosition){
    ;
}

void Ground::update(){
    ;
}

void Ground::draw(){
    Drawable::draw();
    
    glBegin(GL_QUADS);
    
    GLfloat length = 0.5f;
    GLfloat height = 0.1f;
    
    const GLfloat points[8][3] = {
        {0.0f,   0.0f,   0.0f},      //P0
        {length, 0.0f,   0.0f},      //P1
        {length, 0.0f,   -length},   //P2
        {0.0f,   0.0f,   -length},   //P3
        {0.0f,   height, 0.0f},      //P4
        {length, height, 0.0f},      //P5
        {length, height, -length},   //P6
        {0.0f,   height, -length}    //P7
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

}