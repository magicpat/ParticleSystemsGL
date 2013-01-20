//
//  Camera.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Camera__
#define __ParticleSystem__Camera__

#include "LOpenGL.h"
#include "gl_math.h"
#include "Drawable.h"
#include <map>



enum CameraMode
{
    FREE,
    LOOK_AT_DRAWABLE,
    LOOK_AT_POSITION
};

enum CameraMovement
{
    MOVE_LEFT      = 1 << 0, 
    MOVE_RIGHT     = 1 << 1,
    MOVE_FORWARD   = 1 << 2,
    MOVE_BACKWARDS = 1 << 3,
    TURN_LEFT      = 1 << 4,
    TURN_RIGHT     = 1 << 5,
    TURN_UP        = 1 << 6,
    TURN_DOWN      = 1 << 7,
    RISE_UP        = 1 << 8,
    LOWER_DOWN     = 1 << 9
};

class Camera : public Drawable {
public:
	Camera();	
    
    virtual void update(int delta);
    virtual void draw();
    
    //Sets the next mouse-movement to be used in the calculation
    void setMousePosition(Vector2D mouse_movement);
    void addRotation(Vector2D rotation);
    
    //Pushes a movement to the movement stack
    void toggleMovement(CameraMovement movement);
    
    //True if the given movement is currently toggled
    bool isMovementSet(CameraMovement movement);
    
    //Set the movement speed
    void setSpeed(double speed);
    
    //Some methods to let the camera lock on positions
    void lookAt(Drawable* d);
    void lookAt(Vector3D* position);
    void lookFree();
    
private:
    Vector3D m_up;
    CameraMode m_mode;
    Vector3D m_direction;
    Vector3D m_right;
    Vector2D m_rotation_movement;
    GLdouble m_speed;
    
    GLint m_movement_bits; //8 bit for possible movements
    
    Drawable* m_lookDrawable;
    Vector3D* m_lookPosition;
    
    //Pre-Rendering methods (for update)
    void calculateTranslation(int delta);
    void calculateRotation(int delta);
};

#endif /* defined(__ParticleSystem__Camera__) */
