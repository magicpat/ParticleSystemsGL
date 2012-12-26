//
//  first_try.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 26.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "fontain.h"

#include "RenderManager.h"
#include <stdio.h>
#include <math.h>


Fontain::Fontain() : Drawable(){
    glCreateParticles();
    
    m_textures[0] = LoadTextureRAW( "particle_mask.raw", 256, 256);
    m_textures[1] = LoadTextureRAW( "particle.raw", 256, 256 );
}

Fontain::~Fontain(){
    ;
}

void Fontain::square (void) {
    glBindTexture( GL_TEXTURE_2D, m_textures[0] );
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0);
    glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0);
    glVertex2d(1.0,-1.0);
    glTexCoord2d(1.0,1.0);
    glVertex2d(1.0,1.0);
    glTexCoord2d(0.0,1.0);
    glVertex2d(-1.0,1.0);
    glEnd();
}

void Fontain::glCreateParticles (void) {
    int i;
    for (i = 1; i < MAX_PARTICLES; i++)
    {
        m_particles[i].Xpos = 0;
        m_particles[i].Ypos = -5;
        m_particles[i].Zpos = -5;
        m_particles[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                              rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                             ) * rand()%11) + 1) * 0.005);
        m_particles[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                              rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                             ) * rand()%11) + 1) * 0.005);
        m_particles[i].Red = 1;
        m_particles[i].Green = 1;
        m_particles[i].Blue = 1;
        m_particles[i].Scalez = 0.25;
        m_particles[i].Direction = 0;
        m_particles[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                       ) - 1 + 1) * rand()%11) + 1) * 0.02;
        m_particles[i].Deceleration = 0.0025;
    }
}

void Fontain::glUpdateParticles(){
    int i;
    for (i = 1; i < MAX_PARTICLES; i++)
    {
        
        glColor3f (m_particles[i].Red, m_particles[i].Green,
                   m_particles[i].Blue);
        
        m_particles[i].Ypos = m_particles[i].Ypos + m_particles[i]
        .Acceleration - m_particles[i].Deceleration;
        m_particles[i].Deceleration = m_particles[i].Deceleration +
        0.0025;
        
        m_particles[i].Xpos = m_particles[i].Xpos + m_particles[i].Xmov;
        m_particles[i].Zpos = m_particles[i].Zpos + m_particles[i].Zmov;
        
        m_particles[i].Direction = m_particles[i].Direction + ((((((int
                                                                    )(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);
        
        if (m_particles[i].Ypos < -5)
        {
            m_particles[i].Xpos = 0;
            m_particles[i].Ypos = -5;
            m_particles[i].Zpos = -5;
            m_particles[i].Red = 1;
            m_particles[i].Green = 1;
            m_particles[i].Blue = 1;
            m_particles[i].Direction = 0;
            m_particles[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                              ) - 1 + 1) * rand()%11) + 1) * 0.02;
            m_particles[i].Deceleration = 0.0025;
        }
        
    }
}

void Fontain::update() {
    glUpdateParticles();
}

void Fontain::draw() {
    int i;
    for (i = 1; i < MAX_PARTICLES; i++)
    {
        glPushMatrix();
        
        glTranslatef (m_particles[i].Xpos, m_particles[i].Ypos, m_particles[i].Zpos);
        glRotatef (m_particles[i].Direction - 90, 0, 0, 1);
        
        glScalef (m_particles[i].Scalez, m_particles[i].Scalez, m_particles[i].Scalez);
        
        glDisable (GL_DEPTH_TEST);
        glEnable (GL_BLEND);
        
        glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBindTexture (GL_TEXTURE_2D, m_textures[0]);
        
        glBegin (GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f (-1, -1, 0);
        glTexCoord2d (1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();
        
        glBlendFunc (GL_ONE, GL_ONE);
        glBindTexture (GL_TEXTURE_2D, m_textures[1]);
        
        glBegin (GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f (-1, -1, 0);
        glTexCoord2d (1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();
        
        glEnable(GL_DEPTH_TEST);
        
        glPopMatrix();
        
    }
}

/**
void Fontain::display () {
    glClearDepth (1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef (0,0,-10);
    
    glUpdateParticles();
    glDrawParticles();
    glutSwapBuffers();
}
 **/


/*
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
 */

//function to load the RAW file

GLuint Fontain::LoadTextureRAW( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    
    data = (unsigned char *)malloc( width * height * 3 );
    
    fread( data, width * height * 3, 1, file );
    fclose( file );
    
    glGenTextures(1, &texture );            
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    free( data );
    
    return texture;
}

void Fontain::FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );
}