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
#include "Input.h"
#include "HUD.h"
#include "TextureLoader.h"


int main( int argc, char* args[] )
{
    try{
        if(argc == 1){
            std::cerr << "Wrong parameters! Needs [resource_dir_path] as argument" << std::endl;
            return 1;
        }
        
        //Create the most important application components
        Camera camera;
        TextureLoader texture_loader(args[1]);
        Game game(&camera, &texture_loader);
        HUD hud(Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, &camera);
        
        //Create the window the application will be rendered to
        Window window(argc, args, &game, &camera, &hud);
        
        //Create some additional application components
        Input input(&game, &camera, &window);
        
        //Enable mouse and keyboard before starting the listeners
        input.setKeyboardEnabled(true);
        input.setMouseEnabled(true);
        
        //Start the functionality of Input and gamelogic
        input.listen();
        game.start();
        
        //Start GLUT main loop
        glutMainLoop();
    }catch(GLenum error){
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    }
 
    return 0;
}

