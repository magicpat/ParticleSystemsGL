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
#include "TextureLoader.h"

class Game : public Drawable {
public:
    void processKeyboardInput(const unsigned char c);
    void start();
    
    Game(Camera* camera, TextureLoader* texture_loader);
    virtual ~Game();
    
    //Methods derrived from Drawable
    virtual void update(int delta);
    virtual void draw();
    
    void addDrawable(Drawable* d);
    
private:
    //Initializes the game - Needs a valid existing window!
    void init();
    
    //The elements to render
    std::vector<Drawable*> m_drawables;
    
    //Constructor-related variables
    Camera* m_camera;
    TextureLoader* m_texture_loader;
};

#endif /* defined(__ParticleSystem__Game__) */
