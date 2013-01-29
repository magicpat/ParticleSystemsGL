//
//  Drawable.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Drawable__
#define __ParticleSystem__Drawable__

#include "LOpenGL.h"
#include "gl_math.h"


class Drawable{
public:
    //Initializes the object at position (0.0, 0.0, 0.0)
    Drawable();
    Drawable(Vector3D startPosition);
    virtual ~Drawable();
    
    virtual void update(int delta) = 0;
    virtual void draw() = 0;
    
    void setPosition(Vector3D position);
    Vector3D getPosition();

    void setCameraDistance(Vector3D camera_distance);
    Vector3D getCameraDistance();
    
	virtual void rotate(Vector3D angles);
    void translate(Vector3D direction);
    
    struct AscendingCameraDistanceSort{
        bool operator()(Drawable*& begin, Drawable*& end);
    };
    
protected:
    Vector3D m_position;
    Vector3D m_rotation;
    
    //Distance to the eye
    Vector3D m_camera_distance;
};



#endif /* defined(__ParticleSystem__Drawable__) */
