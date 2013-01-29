//
//  HUD.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 20.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "HUD.h"
#include "LOpenGL.h"
#include <string>
#include <sstream>


HUD::HUD(const int screen_width, const int screen_height, Camera* camera)
    : m_screen_width(screen_width), m_screen_height(screen_height), m_camera(camera)
{
    ;
}

HUD::~HUD()
{
    ;
}

void HUD::update(int delta)
{
    ;
}

void HUD::draw()
{
    //Switch to projection mode
	glMatrixMode(GL_PROJECTION);
    
	//Save previous matrix which contains the settings for the perspective projection
	glPushMatrix();
    
        //Reset matrix
        glLoadIdentity();
        
        //Set a 2D orthographic projection
        gluOrtho2D(0, m_screen_width, 0, m_screen_height);
        
        //Invert the y axis, down is positive
        glScalef(1, -1, 1);
        
        //Mover the origin from the bottom left corner to the upper left corner
        glTranslatef(0, -m_screen_height, 0);
        
        //Switch back to modelview mode
        glMatrixMode(GL_MODELVIEW);
        
        glColor3f(255, 255, 255);
    
        //TODO: build in a flag control?
        renderCameraPosition(5, 20);
        renderCameraDirection(5, 40);
        
        
        glMatrixMode(GL_PROJECTION);

	glPopMatrix();
    
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void HUD::renderCameraPosition(float x, float y)
{
    glPushMatrix();
        glLoadIdentity();
        std::ostringstream temp;
        temp.precision(3);
        Vector3D position = m_camera->getPosition();
        temp << "Position (" << position.x << ", " << position.y << ", " << position.z << ")";
        
        renderSpacedBitmapString(x, y, 2, GLUT_BITMAP_HELVETICA_10, temp.str().c_str());
    glPopMatrix();
}

void HUD::renderCameraDirection(float x, float y)
{
    glPushMatrix();
        glLoadIdentity();
        std::ostringstream temp;
        temp.precision(3);
    
        Vector3D direction = m_camera->getDirection();
        temp << "Direction (" << direction.x << ", " << direction.y << ", " << direction.z << ")";
        
        renderSpacedBitmapString(x, y, 2, GLUT_BITMAP_HELVETICA_10, temp.str().c_str());
    glPopMatrix();
}

void HUD::setOrthographicProjection()
{
	//Switch to projection mode
	glMatrixMode(GL_PROJECTION);
    
	//Save previous matrix which contains the settings for the perspective projection
	glPushMatrix();
    
	//Reset matrix
	glLoadIdentity();
    
	//Set a 2D orthographic projection
	gluOrtho2D(0, m_screen_width, 0, m_screen_height);
    
	//Invert the y axis, down is positive
	glScalef(1, -1, 1);
    
	//Mover the origin from the bottom left corner to the upper left corner
	glTranslatef(0, -m_screen_height, 0);
    
	//Switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void HUD::restorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
    
	// restore previous projection matrix
	glPopMatrix();
    
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void HUD::renderSpacedBitmapString(float x, float y, int spacing, void* font, const char* string)
{
    float posX = x;
    
    for (int i = 0; string[i] != '\0'; i++) {
        char c = string[i];
        
        glRasterPos2f(posX, y);
        glutBitmapCharacter(font, c);
        posX = posX + glutBitmapWidth(font, c) + spacing;
    }
}

void HUD::renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, const char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        char c = string[i];
        glRasterPos2f(x, y + bitmapHeight * i);
        glutBitmapCharacter(font, c);
    }
}