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
    
    //Need to recalculate the direction-vector
    virtual void rotate(Vector3D angles);
    virtual void translate(Vector3D direction);
    
    //Some movement methods
    void forward(double distance);
    void yaw(double val);
    void pitch(double val);
    void sideStep(double val);
    
    void lookAt(Drawable* d);
private:
    Vector3D m_up;
    CameraMode m_mode;
    Vector3D m_direction;
    Vector3D m_side;
    
    Drawable* m_lookDrawable;
    Vector3D m_lookPosition;
    
    
};

#endif /* defined(__ParticleSystem__Camera__) */
