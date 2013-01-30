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

Drawable::Drawable(Vector3D startPosition) : Drawable(startPosition, false)
{
    ;
}

Drawable::Drawable(Vector3D startPosition, bool transparent) : m_position(startPosition), m_rotation(Vector3D()), m_scalefactor(1.0), m_transparent(transparent)
{
    ;
}

Drawable::~Drawable()
{
    ;
}


void Drawable::setPosition(Vector3D position)
{
    m_position = position;
}

Vector3D Drawable::getPosition() const
{
    return m_position;
}

Vector3D Drawable::getRotation() const
{
    return m_rotation;
}

void Drawable::setCameraDistance(GLfloat camera_distance)
{
    this->m_camera_distance = camera_distance;
}

GLfloat Drawable::getCameraDistance() const
{
    return this->m_camera_distance;
}

void Drawable::draw()
{
    //glPushMatrix();
    glTranslatef(m_position.x, m_position.y, m_position.z); //Move back to the actual position
    glScalef(m_scalefactor, m_scalefactor, m_scalefactor);
    glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
    glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
    glRotatef(m_rotation.z , 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 0.0f); //Move to origin
    //glPopMatrix();
}


void Drawable::translate (const Vector3D direction)
{
	addToVector3D(m_position, direction );
}

void Drawable::rotate(const Vector3D rotation){
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

void Drawable::scale(const GLfloat scalefactor)
{
    this->m_scalefactor = scalefactor;
}


bool Drawable::isTransparent() const
{
    return m_transparent;
}

bool Drawable::AscendingCameraDistanceSort::operator()(Drawable*& begin, Drawable*& end)
{
    if(begin->isTransparent() && end->isTransparent())
    {
        return (begin->getCameraDistance() < end->getCameraDistance());
    }
    if(begin->isTransparent())
    {
        return false;
    }
    return true;
    
}
