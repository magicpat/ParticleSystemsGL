//
//  Skybox.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Skybox__
#define __ParticleSystem__Skybox__

#include <iostream>

#include "TextureLoader.h"
#include "Drawable.h"

class Skybox : public Drawable{
public:
    Skybox(Vector3D startPosition, GLfloat length, TextureLoader* texture_loader);
    ~Skybox();
    virtual void update(double delta);
    virtual void draw();
    
    //Getter
    GLfloat getLength() const;
    
private:
    //Constructor-related members
    GLfloat m_length;
    TextureLoader* m_texture_loader;
    
    //Textures for top, right, bottom, left, front, back
    GLuint m_texture[6];
    
    void loadTextures();
};

#endif /* defined(__ParticleSystem__Skybox__) */
