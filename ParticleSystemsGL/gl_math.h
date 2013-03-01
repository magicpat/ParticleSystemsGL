//
//  math.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__math__
#define __ParticleSystem__math__

#include "LOpenGL.h"
#include "math.h"

#define PIdiv180 M_PI/180.0


struct Vector3D  {
    Vector3D();
    Vector3D(GLfloat x, GLfloat y, GLfloat z);
    Vector3D(const Vector3D& v);
	GLfloat x, y, z;
    
    //Non-changing utility methods
    double length() const;
    Vector3D normal() const;
    float dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    
    //State changing utility methods
    void normalize();
    
    //Various arithmetic operator overloads
    Vector3D operator-() const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator*(const GLfloat scalar) const;
    
    //Various assignment operator overloads
    Vector3D& operator=(const Vector3D& other);
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    
};

struct Vector2D
{
    Vector2D();
    Vector2D(GLfloat x, GLfloat y);
    
    //Various arithmetic operator overloads
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator*(const GLfloat scalar) const;
    
    //Assignment operator overloads
    Vector2D& operator=(const Vector2D& other);
    
	GLfloat x, y;
};

//Converts Euler-Angles to axis-values (side, up and forward)
void anglesToAxis(const Vector3D &angles, Vector3D &side, Vector3D &up, Vector3D &forward);


//Some Vector-Arithmetic functions
Vector3D addVector3D (const Vector3D v1, const Vector3D v2);
void addToVector3D (Vector3D &target, const Vector3D addend);
void crossProductVector3D(const Vector3D v1, const Vector3D v2, Vector3D &result);
void normalizeVector3D(Vector3D &v);


#endif /* defined(__ParticleSystem__math__) */
