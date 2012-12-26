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


class Drawable{
public:
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif /* defined(__ParticleSystem__Drawable__) */
