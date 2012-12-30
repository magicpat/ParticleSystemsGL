//
//  Camera.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Camera.h"
#include "math.h"
#include "gl_math.h"


Camera::Camera() : Drawable(), m_up(Vector3D(0.0f, 1.0f, 0.0f)),
                               m_mode(CameraMode::FREE),
                               m_direction({0.0f, 0.0f, -1.0f}),
                               m_side({1.0f, 0.0f, 0.0f})
{
    
}

void Camera::update(){
    ;
}


void Camera::lookAt(Drawable* d)
{
    m_lookDrawable = d;
    m_mode = CameraMode::LOOK_AT_DRAWABLE;
}


void Camera::rotate(Vector3D angles){
    Drawable::rotate(angles);
}

void Camera::translate(Vector3D direction){
    Drawable::translate(direction);
    addToVector3D(m_direction, direction);
}

void Camera::forward(double distance){
    m_position.x += distance * m_direction.x;
    m_position.y += distance * m_direction.y;
    m_position.z += distance * m_direction.z;
}

void Camera::sideStep(double val){
    Vector3D yaw = {3.0f, 0.0f, 0.0f};
    
    crossProductVector3D(m_up, m_direction, yaw);
    
    m_position.x += val * yaw.x;
    m_position.y += val * yaw.y;
    m_position.z += val * yaw.z;
}

void Camera::pitch(double val){
    double x = m_direction.x;
    double y = m_direction.z;
    
    m_direction.y += val/100.0;
    m_rotation.x = atan2(m_direction.y, sqrt(x * x + y * y)) * 180.0 / PI;
}

void Camera::yaw(double val){
    double x = m_direction.x;
    double y = m_direction.z;
    double r = sqrt(x*x + y*y);
    double theta = atan2(y,x);
    
    theta += val/40.0;
    
    m_direction.x = r * cos(theta);
    m_direction.z = r * sin(theta);
    normalizeVector3D(m_direction);
    
    //convert to degrees, opengl degrees..
    //minus crap adjustment
    m_rotation.y = -theta * 180.0 / PI;
}

void Camera::draw()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    anglesToAxis(m_rotation, m_side, m_up, m_direction);
    
    switch(m_mode){
        case CameraMode::FREE:
            gluLookAt(m_position.x, m_position.y, m_position.z,
                      m_direction.x, m_direction.y, m_direction.z,
                      m_up.x, m_up.y, m_up.z);
            break;
        case CameraMode::LOOK_AT_DRAWABLE:
            gluLookAt(m_position.x, m_position.y, m_position.z,
                      m_lookDrawable->getPosition().x, m_lookDrawable->getPosition().y, m_lookDrawable->getPosition().z,
                      m_up.x, m_up.y, m_up.z);
            break;
            
        case CameraMode::LOOK_AT_POSITION:
            gluLookAt(m_position.x, m_position.y, m_position.z,
                      m_lookPosition.x, m_lookPosition.y, m_lookPosition.z,
                      m_up.x, m_up.y, m_up.z);
            break;
    }
     
}

