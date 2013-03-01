
//
//  Camera.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Camera.h"
#include "gl_math.h"


Camera::Camera() : Drawable(), m_up(Vector3D(0.0f, 1.0f, 0.0f)),
                               m_mode(CameraMode::FREE),
                               m_direction({0.0f, 0.0f, -1.0f}),
                               m_right({1.0f, 0.0f, 0.0f}),
                               m_speed(1),
                               m_rotation_movement(0.0, 0.0),
                               m_movement_bits(0)
{
    
}

Camera::~Camera()
{
    ;
}

void Camera::setDirection(const Vector3D direction)
{
    m_direction = direction;
}

void Camera::update(double delta)
{
    calculateRotation(delta);
    calculateTranslation(delta);
    
    m_direction = Vector3D(sinf(m_rotation.x), tanf(m_rotation.y), cosf(m_rotation.x));
    m_right = Vector3D(m_direction.z, 0, m_direction.x);
}

void Camera::lookAt(Drawable* d)
{
    Vector3D d_position = d->getPosition();
    m_direction = d_position;
    gluLookAt(m_position.x, m_position.y, m_position.z,
              d_position.x, d_position.y, d_position.z,
              m_up.x, m_up.y, m_up.z);
}

void Camera::lookAt(Vector3D* position)
{
    m_direction = Vector3D(*position);
    gluLookAt(m_position.x, m_position.y, m_position.z,
              position->x, position->y, position->z,
              m_up.x, m_up.y, m_up.z);
}

void Camera::snapAt(Vector3D* position)
{
    if(position){
        m_lookPosition = position;
        m_mode = CameraMode::LOOK_AT_POSITION;
    }
}

void Camera::snapAt(Drawable* d)
{
    if(d)
    {
        m_lookDrawable = d;
        m_mode = CameraMode::LOOK_AT_DRAWABLE;
    }
}

void Camera::lookFree()
{
    //TODO: Clear m_lookPosition and m_lookDrawable? Not sure
    m_mode = CameraMode::FREE;
}

Vector3D Camera::getDirection()
{
    return m_direction;
}

void Camera::toggleMovement(CameraMovement movement)
{
    m_movement_bits ^= movement;
}

void Camera::clearMovement()
{
    m_movement_bits = 0x0000;
}

bool Camera::isMovementSet(CameraMovement movement)
{
    return m_movement_bits & movement;
}

void Camera::addRotation(Vector2D rotation)
{
    m_rotation_movement = rotation;
}

void Camera::calculateTranslation(double delta)
{
    if(m_movement_bits == 0)
    {
        return;
    }
    
	Vector3D movement(0.f, 0.f, 0.f);
	Vector3D forward = Vector3D(sinf(m_rotation.x), 0, cosf(m_rotation.x));
	Vector3D right   = Vector3D(-forward.z, 0, forward.x);
    Vector3D up      = right.cross(forward);
    
	if(isMovementSet(CameraMovement::MOVE_LEFT))
	{
		movement -= right;
	}
    
	if(isMovementSet(CameraMovement::MOVE_RIGHT) )
	{
		movement += right;
	}
    
	if(isMovementSet(CameraMovement::MOVE_FORWARD) )
	{
		movement += forward;
	}
    
	if(isMovementSet(CameraMovement::MOVE_BACKWARDS))
	{
		movement -= forward;
	}
    
    if(isMovementSet(CameraMovement::RISE_UP))
    {
        movement += up;
    }
    
    if(isMovementSet(CameraMovement::LOWER_DOWN))
    {
        movement -= up;
    }
    
    if(movement.length() != 0){
        //Normalize movement and adjust the movement-speed
        movement.normalize();
		movement = movement * (m_speed * 50) * delta;
        
        //Add the movement to the position
		m_position += movement;
    }
}

void Camera::calculateRotation(double delta)
{
	static const float kRotationSpeed = (m_speed/50) * delta ;
    
    m_rotation.x += m_rotation_movement.x * kRotationSpeed;
    m_rotation.y += m_rotation_movement.y * kRotationSpeed;
    
	if(m_rotation.y < -(M_PI / 2) + 0.1)
	{
		m_rotation.y = -(M_PI / 2) + 0.1;
	}
    
	if(m_rotation.y > (M_PI / 2) - 0.1)
	{
		m_rotation.y = (M_PI / 2) - 0.1;
	}
    
    //Clear the added rotation, so it won't be added in the next update
    m_rotation_movement.x = m_rotation_movement.y = 0.0f;
    
    //Add rotation if there is a X-movement activated
    if(isMovementSet(CameraMovement::TURN_RIGHT)){
        m_rotation_movement.x += -1.0 * m_speed * delta;
    }
    
    if(isMovementSet(CameraMovement::TURN_LEFT)){
        m_rotation_movement.x += 1.0 * m_speed * delta;
    }
}

void Camera::draw()
{
    glLoadIdentity();

    switch(m_mode){
        case CameraMode::FREE:
            gluLookAt(m_position.x, m_position.y, m_position.z,
                      m_position.x + m_direction.x, m_position.y + m_direction.y, m_position.z + m_direction.z,
                      m_up.x, m_up.y, m_up.z);
            break;
        case CameraMode::LOOK_AT_DRAWABLE:
            lookAt(m_lookDrawable);
            break;
            
        case CameraMode::LOOK_AT_POSITION:
            lookAt(m_lookPosition);
            break;
    }
}

