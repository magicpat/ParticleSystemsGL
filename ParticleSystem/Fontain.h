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
    
    Fontain(Vector3D startPosition);
    Fontain();
    ~Fontain();
    
    virtual void update();
    virtual void draw();
    
private:
    GLuint LoadTextureRAW( const char * filename, int width, int height );
    void FreeTexture( GLuint texturez );
    void square ();
    void glCreateParticles();
    void glUpdateParticles();
    
    GLfloat m_textures[10];
    GLfloat m_radius;
    PARTICLE m_particles[MAX_PARTICLES];
};


#endif 
