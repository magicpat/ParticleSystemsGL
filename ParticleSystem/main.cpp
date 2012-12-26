//
//  main.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "RenderManager.h"
#include "fontain.h"

int main( int argc, char* args[] )
{
    RenderManager renderManager;
    
    bool initialized = renderManager.init(argc, args);

     //Do post window/context creation initialization
     if( !initialized)
     {
         printf( "Unable to initialize graphics library!\n" );
         return 1;
     }
    
    Drawable* fontain = new Fontain;
    renderManager.addDrawable(fontain);

    //Start GLUT main loop
    glutMainLoop();
 
    return 0;
}

