///
//  Viewing
//
//  Simple module for setting up the viewing and projection transforms
//  for the Transformation Assignment.
//
//  Created by Warren R. Carithers 2016/11/11.
//  Based on code created by Joe Geigel on 1/23/13.
//  Last updated 2019/04/04 by wrc.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  Wei Zeng
///

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Viewing.h"

///
// This function sets up the view and projection parameters for the
// desired projection of the scene. See the assignment description for
// the values for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param mode - The desired projection mode (Frustum or Ortho)
///
void setUpProjection( GLuint program, ViewMode mode)
{
    // Add your code here.
	int index = glGetUniformLocation(program, "projection");

	if (mode == Frustum) {
		//0 is Frustum mode
		glUniform1f(index, 0.0);
	}

	if (mode == Ortho) {
		//1 is Ortho mode 
		glUniform1f(index, 1.0);
	}
}

///
// This function clears any model transformations, setting the values
// to the defaults: no scaling (scale factor of 1), no rotation (degree
// of rotation = 0), and no translation (0 translation in each direction).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearTransforms( GLuint program )
{
    // Add your code here.
	GLfloat translation[] = { 0.0, 0.0, 0.0 };
	int indexT = glGetUniformLocation(program, "translation");
	glUniform3fv(indexT, 1, translation);

	GLfloat scale[] = { 1.0, 1.0, 1.0 };
	int indexS = glGetUniformLocation(program, "scale");
	glUniform3fv(indexS, 1, scale);

	GLfloat rotation[] = { 0.0, 0.0, 0.0 };
	int indexR = glGetUniformLocation(program, "rotation");
	glUniform3fv(indexR, 1, rotation);
}

///
// This function sets up the transformation parameters for the vertices
// of the teapot.  The order of application is specified in the driver
// program.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param scale  - scale factors for each axis
// @param rotate - rotation angles around the three axes, in degrees
// @param xlate  - amount of translation along each axis
///
void setUpTransforms( GLuint program, Tuple scale, Tuple rotate, Tuple xlate )
{
    // Add your code here.
	GLfloat translation[] = { xlate.x, xlate.y, xlate.z };
	int indexT = glGetUniformLocation(program, "translation");
	glUniform3fv(indexT, 1, translation);

	GLfloat sca[] = { scale.x, scale.y, scale.z };
	int indexS = glGetUniformLocation(program, "scale");
	glUniform3fv(indexS, 1, sca);

	GLfloat rotation[] = { rotate.x, rotate.y, rotate.z };
	int indexR = glGetUniformLocation(program, "rotation");
	glUniform3fv(indexR, 1, rotation);
}

///
// This function clears any changes made to camera parameters, setting the
// values to the defaults: eye (0.0,0.0,0.0), lookat (0,0,0.0,-1.0),
// and up vector (0.0,1.0,0.0).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearCamera( GLuint program )
{
    // Add your code here.
	GLfloat eye[] = { 0.0, 0.0, 0.0 };
	int indexE = glGetUniformLocation(program, "eye");
	glUniform3fv(indexE, 1, eye);

	GLfloat lookat[] = { 0.0, 0.0, -1.0 };
	int indexL = glGetUniformLocation(program, "lookat");
	glUniform3fv(indexL, 1, lookat);

	GLfloat upvector[] = { 0.0, 1.0, 0.0 };
	int indexU = glGetUniformLocation(program, "upvector");
	glUniform3fv(indexU, 1, upvector);
}

///
// This function sets up the camera parameters controlling the viewing
// transformation.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param eye    - camera location
// @param lookat - lookat point
// @param up     - the up vector
///
void setUpCamera( GLuint program, Tuple eye, Tuple lookat, Tuple up )
{
    // Add your code here.
	GLfloat eyeArr[] = { eye.x, eye.y, eye.z };
	int indexE = glGetUniformLocation(program, "eye");
	glUniform3fv(indexE, 1, eyeArr);

	GLfloat lookatArr[] = { lookat.x, lookat.y, lookat.z };
	int indexL = glGetUniformLocation(program, "lookat");
	glUniform3fv(indexL, 1, lookatArr);

	GLfloat upvectorArr[] = { up.x, up.y, up.z };
	int indexU = glGetUniformLocation(program, "upvector");
	glUniform3fv(indexU, 1, upvectorArr);

}
