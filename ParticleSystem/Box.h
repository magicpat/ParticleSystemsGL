//
//  Box.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Box__
#define __ParticleSystem__Box__

#include "Drawable.h"

class Box : public Drawable{
public:
    Box(Vector3D startPosition, GLfloat length, GLfloat width, GLfloat height);
    
    virtual void update(int delta);
    virtual void draw();
    
private:
    GLfloat m_length;
    GLfloat m_width;
    GLfloat m_height;
};

#endif /* defined(__ParticleSystem__Box__) */
