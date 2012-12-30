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

#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0


struct Vector3D  {
    Vector3D();
    Vector3D(GLfloat x, GLfloat y, GLfloat z);
	GLfloat x, y, z;
};

struct Vector2D
{
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
