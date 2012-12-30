//
//  main.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "Window.h"
#include "fontain.h"
#include "Camera.h"
#include "Keyboard.h"


int main( int argc, char* args[] )
{
    try{
        //Create the most important application components
        Camera camera;
        Game game(&camera);
        Window window(argc, args, &game, &camera);
        
        //Create some additional application components
        Keyboard keyboard(&game, &camera, &window);
        
        //Start the functionality of keyboard and gamelogic
        keyboard.listen();
        game.start();
        
        //Start GLUT main loop
        glutMainLoop();
    }catch(GLenum error){
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    }
 
    return 0;
}

