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
                               m_side({1.0f, 0.0f, 0.0f}),
                               m_speed(0.1),
                               m_center({0.0f, 0.0f, 0.0f}),
                               m_diameter(100.0f)
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

void Camera::lookAt(Vector3D* position){
    if(position != NULL){
        m_lookPosition = position;
        m_mode = CameraMode::LOOK_AT_POSITION;
    }
}


void Camera::rotate(Vector3D angles){
    Drawable::rotate(angles);
}

void Camera::translate(Vector3D movement){
    addToVector3D(m_position, movement);
    addToVector3D(m_direction, movement);
}

void Camera::lookFree(){
    //TODO: Clear m_lookPosition and m_lookDrawable? Not sure
    m_mode = CameraMode::FREE;
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

void Camera::strafe(double val){
    Vector3D movement = { val, 0.0f, 0.0f };
    this->translate(movement);
}

void Camera::pitch(double val){
    double x = m_direction.x;
    double y = m_direction.z;
    
    m_direction.y += val/100.0;
    normalizeVector3D(m_direction);
    
    m_rotation.x = atan2(m_direction.y, sqrt(x * x + y * y)) * 180.0 / PI;
}

void Camera::yaw(double val){
    double x = m_direction.x;
    double z = m_direction.z;
    
    double r = sqrt(x*x + z*z); //Length of the vector and hypotenuse of the triangle
    double theta = atan2(z, x); //Get the angle for z/x
    
    theta -= val / 40; //Add value to the angle between z/x
    
        
    //Set the direction coordinates with the new angle
    m_direction.x = r * cos(theta);
    m_direction.z = r * sin(theta);
    
    //Normalization to prevent values > 1
    normalizeVector3D(m_direction);

    //convert to degrees, opengl degrees..
    //m_rotation.y = -theta * 180.0 / PI;
    m_rotation.y = theta;
}

void Camera::draw()
{
    //Set the bounding-sphere for the view
    /*
    GLfloat zNear = 1.0f;
    GLfloat zFar = zNear + m_diameter;
    
    GLdouble left = m_center.x - m_diameter;
    GLdouble right = m_center.x + m_diameter;
    GLdouble bottom = m_center.y - m_diameter;
    GLdouble top = m_center.y + m_diameter;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, zNear, zFar);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */
    
    printf("m_rotation: %f , %f,  %f\n", m_rotation.x, m_rotation.y, m_rotation.z);
    printf("m_direction: %f , %f,  %f\n", m_direction.x, m_direction.y, m_direction.z);
    printf("m_position: %f , %f,  %f\n", m_position.x, m_position.y, m_position.z);
    printf("m_up: %f , %f,  %f\n\n", m_up.x, m_up.y, m_up.z);
    
    /*
    glTranslatef(-m_position.x, -m_position.y, -m_position.z); //Move back to the actual position
    glRotatef(m_rotation.x , 1.0, 0.0, 0.0);
    glRotatef(m_rotation.y , 0.0, 1.0, 0.0);
    glRotatef(m_rotation.z , 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 0.0f); //Move to origin
    */
    
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
                      m_lookPosition->x, m_lookPosition->y, m_lookPosition->z,
                      m_up.x, m_up.y, m_up.z);
            break;
    }
}

