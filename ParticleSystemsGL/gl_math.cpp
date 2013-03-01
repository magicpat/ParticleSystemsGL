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


Vector3D addVector3D (const Vector3D v1, const Vector3D v2)
{
	Vector3D result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
    
	return result;
}

// Vector3D vec = Vector3D(1,1,1);
// addToVector3D(vec, Vector3D(2,2,2));

//

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

/******************************************
 Vector3D
 *****************************************/
Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f){
    ;
}


Vector3D::Vector3D(GLfloat x, GLfloat y, GLfloat z ) : x(x), y(y), z(z){
}

Vector3D::Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z)
{
    ;
}

double Vector3D::length() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3D::dot(const Vector3D& other) const
{
    return x*other.x + y*other.y + z*other.z;
}

Vector3D Vector3D::normal() const
{
    Vector3D v = Vector3D(*this);
    v.normalize();
    return v;
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
    Vector3D result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    result.normalize();
    
    return result;
}

void Vector3D::normalize()
{
    double length = this->length();
    
    if(length != 0)
    {
        x /= length;
        y /= length;
        z /= length;
    }
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(x * -1, y * -1, z * -1);
}

Vector3D Vector3D::operator*(const GLfloat scalar) const
{
    return Vector3D(x*scalar, y*scalar, z*scalar);
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    if(this != &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    if(this != &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    return *this;
}

/******************************************
 Vector2D
 *****************************************/
Vector2D::Vector2D() : x(0.0), y(0.0)
{
    ;
}

Vector2D::Vector2D(GLfloat x, GLfloat y) : x(x), y(y)
{
    ;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(const GLfloat scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}