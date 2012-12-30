//
//  math.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 27.12.12.
//  Copyright (c) 2012 Patrick Stapfer. All rights reserved.
//

#include "gl_math.h"
#include "math.h"
#include <cmath>

Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f){
    ;
}

Vector3D::Vector3D(GLfloat x, GLfloat y, GLfloat z ) : x(x), y(y), z(z){
}

Vector3D addVector3D (const Vector3D v1, const Vector3D v2)
{
	Vector3D result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
    
	return result;
}

void addToVector3D (Vector3D &target, const Vector3D addend)
{
	target.x += addend.x;
	target.y += addend.y;
	target.z += addend.z;
}

void crossProductVector3D(const Vector3D v1, const Vector3D v2, Vector3D &result){
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    normalizeVector3D(result);
}

void normalizeVector3D(Vector3D &v){
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    
    v.x /= length;
    v.y /= length;
    v.z /= length;
}

///////////////////////////////////////////////////////////////////////////////
// convert Euler angles(x,y,z) to axis(side, up, forward)
// The order of rotation is Yaw->Pitch->Roll (Ry*Rx*Rz)
// Rx: rotation about X-axis, pitch
// Ry: rotation about Y-axis, yaw(heading)
// Rz: rotation about Z-axis, roll
//      Ry         Rx          Rz
// |Cy  0 -Sy| |1   0  0| | Cz Sz 0|   |CyCz-SySxSz  CySz+SySxCz  -SyCx|  <- side
// | 0  1   0|*|0  Cx Sx|*|-Sz Cz 0| = |-CxSz        CxCz         Sx   |  <- up
// |Sy  0  Cy| |0 -Sx Cx| |  0  0 1|   |SyCz+CySxSz  SySz-CySxCz  CyCx |  <- forward
///////////////////////////////////////////////////////////////////////////////
void anglesToAxis(const Vector3D &angles, Vector3D &side, Vector3D &up, Vector3D &forward)
{
    const float DEG2RAD = 3.141593f / 180;
    float sx, sy, sz, cx, cy, cz, theta;
    
    // rotation angle about X-axis (pitch)
    theta = angles.x * DEG2RAD;
    sx = sinf(theta);
    cx = cosf(theta);
    
    // rotation angle about Y-axis (yaw)
    theta = angles.y * DEG2RAD;
    sy = sinf(theta);
    cy = cosf(theta);
    
    // rotation angle about Z-axis (roll)
    theta = angles.z * DEG2RAD;
    sz = sinf(theta);
    cz = cosf(theta);
    
    // determine side vector
    side.x = cy*cz - sy*sx*sz;
    side.y = cy*sz + sy*sx*cz;
    side.z = -sy*cx;
    
    // determine up vector
    up.x = -cx*sz;
    up.y = cx*cz;
    up.z = sx;
    
    // determine forward vector
    forward.x = sy*cz + cy*sx*sz;
    forward.y = sy*sz - cy*sx*cz;
    forward.z = cy*cx;
}