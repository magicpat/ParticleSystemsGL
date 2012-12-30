//
//  Ground.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Ground__
#define __ParticleSystem__Ground__

#include "Drawable.h"

class Ground : public Drawable{
public:
    Ground();
    Ground(Vector3D startPosition);
    
    virtual void update();
    virtual void draw();
};

#endif /* defined(__ParticleSystem__Ground__) */
