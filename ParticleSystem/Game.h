//
//  Game.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__Game__
#define __ParticleSystem__Game__

#include <vector>
#include "Drawable.h"
#include "Camera.h"

class Game : public Drawable {
public:
    void processKeyboardInput(const unsigned char c);
    void start();
    
    Game(Camera* camera);
    
    //Methods derrived from Drawable
    virtual void update(int delta);
    virtual void draw();
    
    void addDrawable(Drawable* d);
    
private:
    //Initializes the game - Needs a valid existing window!
    void init();
    
    //The elements to render
    std::vector<Drawable*> m_drawables;
    Camera* m_camera;
};

#endif /* defined(__ParticleSystem__Game__) */
