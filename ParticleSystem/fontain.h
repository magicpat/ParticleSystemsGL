//
//  first_try.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__fontain__
#define __ParticleSystem__fontain__

#include "LUtil.h"


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
}PARTICLES;

GLuint LoadTextureRAW( const char * filename, int width, int height );
void FreeTexture( GLuint texturez );
void square ( void );
void glCreateParticles( void );
void glUpdateParticles( void );
void glDrawParticles( void );


#endif 
