//
//  LUtil.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "LOpenGL.h"
#include "RenderManager.h"

//Initialize static members
std::vector<Drawable*> RenderManager::m_drawables;

RenderManager::RenderManager(){

}

bool RenderManager::init(int argc, char* args[])
{
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
    
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();
    
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    
    //Set rendering function
    glutDisplayFunc( RenderManager::render );
    
    //Set reshape callback
    glutReshapeFunc (reshape);
    
    //Set the run-callback for the mainloop
    glutTimerFunc( 1000 / RenderManager::SCREEN_FPS, RenderManager::run, 0 );
    
    return true;
}


void RenderManager::addDrawable(Drawable* d){
    RenderManager::m_drawables.push_back(d);
}
 

void RenderManager::update()
{
    
}

void RenderManager::render()
{
    glClearDepth (1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0,0,-10);
    
    for(std::vector<Drawable*>::size_type i = 0; i != m_drawables.size(); i++) {
        m_drawables[i]->update();
    }
    
    for(std::vector<Drawable*>::size_type i = 0; i != m_drawables.size(); i++) {
        m_drawables[i]->draw();
    }
    
    //Update screen
    glutSwapBuffers();
}   

void RenderManager::reshape (int width, int height) {
    glViewport (0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void RenderManager::run( int val ){
    //Frame logic
    RenderManager::update();
    RenderManager::render();
    
    //Run frame one more time
    glutTimerFunc( 1000 / RenderManager::SCREEN_FPS, RenderManager::run, val );
}
