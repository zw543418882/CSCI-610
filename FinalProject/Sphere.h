///
//  Sphere.h
//
//  Prototypes for shape-drawing functions.
//
//  Created by Warren R. Carithers 2018/11/28.
//  Based on earlier versions by Warren R. Carithers and Joe Geigel.
//  Last updated 2019/04/13 by wrc.
//  Copyright 2018 Rochester Institute of Technology.  All rights reserved.
//
//  This file should not be modified by students.
///

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Shapes.h"
#include "Canvas.h"
#include "Buffers.h"

///
// makeSphere
//
// Invoked whenever a sphere must be created
//
// @param C - Canvas being used
///
void makeSphere( Canvas &C );

///
// drawSphere
//
// Invoked whenever the sphere must be redrawn
//
// @param pshader - shader program for Phong shading
// @param tshader - shader program for texture mapping
// @param bset    - the BufferSet containing the object's data
///
void drawSphere( GLuint pshader, GLuint tshader, BufferSet &bset );

#endif
