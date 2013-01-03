//
//  Drawable.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Drawable.h"
#include "math.h"

Drawable::Drawable() : Drawable(Vector3D(0.0f, 0.0f, 0.0f))
{
    ;
}

Drawable::Drawable(Vector3D startPosition) : m_position(startPosition), m_rotation()
{
    ;
}


void Drawable::setPosition(Vector3D position)
{
    m_position = position;
}

Vector3D Drawable::getPosition()
{
    return m_position;
}

void Drawable::draw()
{
    //glPushMatrix();
    //glLoadIdentity();
    glTranslatef(m_position.x, m_position.y, m_position.z); //Move back to the actual position
    glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
    glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
    glRotatef(m_rotation.z , 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 0.0f); //Move to origin
    //glPopMatrix();
}


void Drawable::translate (Vector3D direction)
{
	addToVector3D(m_position, direction );
}

void Drawable::rotate(Vector3D rotation){
    m_rotation.x += rotation.x;
    m_rotation.y += rotation.y;
    m_rotation.z += rotation.z;
    
    if(m_rotation.x > 360.0f){
        m_rotation.x -= 360.0f;
    }
    
    if(m_rotation.x < -360.0f){
        m_rotation.x += 360.0f;
    }
    
    if(m_rotation.y > 360.0f){
        m_rotation.y -= 360.0f;
    }
    
    if(m_rotation.y < -360.0f){
        m_rotation.y += 360.0f;
    }
    
    if(m_rotation.z > 360.0f){
        m_rotation.z -= 360.0f;
    }
    
    if(m_rotation.z < -360.0f){
        m_rotation.z += 360.0f;
    }
}

void Drawable::rotateY (GLfloat angle)
{
	rotate(Vector3D(0.0f, angle, 0.0f));
}

void Drawable::rotateX (GLfloat angle)
{
	rotate(Vector3D(angle, 0.0f, 0.0f));
}

void Drawable::rotateZ (GLfloat angle)
{
	rotate(Vector3D(0.0f, 0.0f, angle));
}

void Drawable::translateX(GLfloat distance)
{
	translate(Vector3D(distance, 0.0f, 0.0f));
}

void Drawable::translateY(GLfloat distance)
{
    translate(Vector3D(0.0f,distance, 0.0f));
}

void Drawable::translateZ(GLfloat distance)
{
    translate(Vector3D(0.0f, 0.0f, distance));
}

