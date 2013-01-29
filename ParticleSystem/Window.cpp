//
//  Window.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "LOpenGL.h"
#include "Window.h"

Game* Window::m_game;
Camera* Window::m_camera;
HUD* Window::m_hud;

int lastDelta;
int currentDelta;

Window::Window(int argc, char* args[], Game* game, Camera* camera, HUD* hud): m_window(0){
    Window::m_game = game;
    Window::m_camera = camera;
    Window::m_hud = hud;
    
    //Initialize FreeGLUT
    glutInit( &argc, args );
    
    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );
    
    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    this->m_window = glutCreateWindow( "Simple Particle Systems" );
    
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Enable Texturizing
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );
    glFrontFace(GL_CW);
    
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();
    
    if( error != GL_NO_ERROR )
    {
        throw error;
    }
    
    //Set rendering function
    glutDisplayFunc( Window::display );
    
    //Set reshape callback
    glutReshapeFunc (reshape);
    
    //Set the run-callback for the mainloop
    glutTimerFunc( 1000 / Window::SCREEN_FPS, Window::run, 0 );

}

bool Window::destroy(){
    if(this->m_window > 0){
        glutDestroyWindow(this->m_window);
        return true;
    }
    return false;
}

void Window::reshape (int width, int height) {
    glViewport (0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void Window::display( ){
    // Get the time when the previous frame was rendered
    lastDelta = currentDelta;
    
    // Get the current time (in milliseconds) and calculate the elapsed time
    currentDelta = glutGet(GLUT_ELAPSED_TIME);
    int delta = currentDelta - lastDelta;
    
    //Update game
    Window::m_camera->update(delta);
    Window::m_game->update(delta);
    Window::m_hud->update(delta);
    
    //Clear and set the image to render
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearDepth (1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Blending settings
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Initialize Modelview-Matrix
    glMatrixMode(GL_MODELVIEW);
    
    //glLoadIdentity();
    
    //Transform the Modelview-Matrix to the camera-view
    Window::m_camera->draw();
    
    //Call to the game-logic to draw it's drawables
    Window::m_game->draw();
    
    //Draw the HUD
    Window::m_hud->draw();
    
    
    //Update screen
    glutSwapBuffers();
}

void Window::run(int val){
    Window::display();
    
    //Run frame one more time
    glutTimerFunc( 1000 / Window::SCREEN_FPS, Window::run, val );
}
