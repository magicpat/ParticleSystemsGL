//
//  GlassCube.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 28.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__GlassCube__
#define __ParticleSystem__GlassCube__

#include <iostream>

#include "TextureLoader.h"
#include "Drawable.h"

class GlassCube : public Drawable{
public:
    GlassCube(Vector3D startPosition, GLfloat length, TextureLoader* texture_loader);
    
    virtual void update(int delta);
    virtual void draw();
    
private:
    //Constructor-related members
    GLfloat m_length;
    TextureLoader* m_texture_loader;
    
    //Other members
    GLuint m_texture;
    
    void loadTextures();
};

#endif /* defined(__ParticleSystem__GlassCube__) */
