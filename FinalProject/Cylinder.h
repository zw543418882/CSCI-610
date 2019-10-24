#pragma once
///
//  Cylinder.h
//


#ifndef _Cylinder_H_
#define _Cylinder_H_

#include "Shapes.h"
#include "Canvas.h"
#include "Buffers.h"

///
// makeCylinder
//
// Invoked whenever a Cylinder must be created
//
// @param C - Canvas being used
///
void makeCylinder(Canvas &C);

///
// drawCylinder
//
// Invoked whenever the Cylinder must be redrawn
//
// @param pshader - shader program for Phong shading
// @param tshader - shader program for texture mapping
// @param bset    - the BufferSet containing the object's data
///
void drawCylinder(int obj, GLuint pshader, BufferSet &bset);

#endif
