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



enum CameraMode
{
    FREE,
    LOOK_AT_DRAWABLE,
    LOOK_AT_POSITION
};

class Camera : public Drawable{
public:
	Camera();	
    
    virtual void update();
    virtual void draw();
    
    virtual void translate(Vector3D movement);
    virtual void rotate(Vector3D angles);
    
    //Some movement methods
    void yaw(double val); //Around y - Counterclockwise = +
    void pitch(double val); //Around x - Counterclockwise = +
    void forward(double distance); //Along z - Forward = +
    void sideStep(double val); //Along x - Right = +
    void strafe(double val); //Along x - Right = +
    
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
    Vector3D m_side;
    double m_speed;
    
    //For the bounding-sphere of the view
    Vector3D m_center;
    GLfloat m_diameter;
    
    Drawable* m_lookDrawable;
    Vector3D* m_lookPosition;
    
    
};

#endif /* defined(__ParticleSystem__Camera__) */
