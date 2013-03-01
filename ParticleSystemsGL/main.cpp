//
//  main.cpp
//  ParticleSystemsGL 
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include <string>
#include "Window.h"
#include "fontain.h"
#include "Camera.h"
#include "Input.h"
#include "HUD.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"


int main( int argc, char* args[] )
{
    try{
        std::string current_directory = "";
        
        /*
         TODO: More intuitive path-checking for resources and shaders
        if(argc == 1){
            std::cerr << "Wrong parameters! Needs [resource_dir_path] as argument" << std::endl;
            return 1;
        }
        */
        
        current_directory = current_directory + args[1];
        
        ShaderLoader shader_loader;
        shader_loader.compileFile(GL_VERTEX_SHADER, (current_directory + "/shaders/vertex_shader.txt").c_str());
        
        
        //Create the most important application components
        Camera camera;
        TextureLoader texture_loader(current_directory);
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

