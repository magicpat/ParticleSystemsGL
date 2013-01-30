//
//  Earth.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Earth__
#define __ParticleSystem__Earth__

#include <iostream>
#include "3DS.h"

class Earth : public Model
{
public:
    Earth(TextureLoader* texture_loader);
    
    void update(double delta);
    void draw();
    
private:
    ;
};
#endif /* defined(__ParticleSystem__Earth__) */
