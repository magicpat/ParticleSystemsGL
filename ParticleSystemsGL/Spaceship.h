//
//  Spaceship.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 30.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Spaceship__
#define __ParticleSystem__Spaceship__

#include <iostream>
#include "3DS.h"
#include "Camera.h"

class Spaceship : public Model
{
public:
    Spaceship(TextureLoader* texture_loader);
    
    //To snap the object to the camera position
    Spaceship(TextureLoader* texture_loader, Camera* camera);
    
    void draw();
private:
    Camera* m_camera;
};

#endif /* defined(__ParticleSystem__Spaceship__) */
