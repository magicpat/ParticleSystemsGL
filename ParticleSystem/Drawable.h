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
    Drawable(Vector3D startPosition, bool transparent);
    virtual ~Drawable();
    
    virtual void update(double delta) = 0;
    virtual void draw() = 0;
    
    //Transformations
	virtual void rotate(const Vector3D angles);
    void translate(const Vector3D direction);
    void scale(const GLfloat scalefactor);
    
    //Getter
    bool isTransparent() const;
    Vector3D getPosition() const;
    Vector3D getRotation() const;
    GLfloat getCameraDistance() const;
    
    //Setter
    void setPosition(Vector3D position);
    void setCameraDistance(GLfloat camera_distance);
    
    struct AscendingCameraDistanceSort{
        bool operator()(Drawable*& begin, Drawable*& end);
    };
    
protected:
    Vector3D m_position;
    Vector3D m_rotation;
    GLfloat m_scalefactor;
    bool m_transparent;
    
    //Distance to the eye - Usable for LOD
    GLfloat m_camera_distance;
};



#endif /* defined(__ParticleSystem__Drawable__) */
