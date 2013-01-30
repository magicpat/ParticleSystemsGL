//
//  first_try.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__fontain__
#define __ParticleSystem__fontain__

#include "LOpenGL.h"
#include "Drawable.h"
#include "TextureLoader.h"


typedef struct
{
    double Xpos;
    double Ypos;
    double Zpos;
    double Xmov;
    double Zmov;
    double Red;
    double Green;
    double Blue;
    double Direction;
    double Acceleration;
    double Deceleration;
    double Scalez;
    bool Visible;
} PARTICLE;

class Fontain : public Drawable {
public:
    static const unsigned int MAX_PARTICLES = 500;
    
    Fontain(Vector3D startPosition,  TextureLoader* texture_loader);
    virtual ~Fontain();
    
    //Overridden methods from Drawable
    virtual void update(double delta);
    virtual void draw();
    
private:
    void glCreateParticles();
    void glUpdateParticles(int delta);
    
    GLuint m_texture;
    GLfloat m_radius;
    PARTICLE m_particles[MAX_PARTICLES];
    
    TextureLoader* m_texture_loader;
};


#endif 
