//
//  HUD.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 20.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__HUD__
#define __ParticleSystem__HUD__

#include <iostream>
#include "Drawable.h"
#include "Camera.h"

class HUD : public Drawable
{
public:
    HUD(const int screen_width, const int screen_height, Camera* camera);
    
    virtual void update(int delta);
    virtual void draw();
    
private:
    const int m_screen_height;
    const int m_screen_width;
    Camera* m_camera;
    
    //Projection-Settings
    void setOrthographicProjection();
    void restorePerspectiveProjection();
    
    //Layout rendering methods
    void renderCameraPosition(float x, float y);
    void renderCameraDirection(float x, float y);
    
    //Bitmap-String rendering
    void renderSpacedBitmapString(float x, float y, int spacing, void *font, const char *string);
    void renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, const char *string);
};

#endif /* defined(__ParticleSystem__HUD__) */
