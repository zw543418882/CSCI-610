///
//  Textures
//
//  Simple module for setting up texture mapping parameters.
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Last updated 2019/04/13 by wrc.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//
//  This code can be compiled as either C or C++.
///

#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

#include "Textures.h"
#include "Shapes.h"

// this is here in case you are using SOIL;
// if you're not, it can be deleted.
#include <SOIL.h>

#ifdef __cplusplus
using namespace std;
#endif

// Add any global definitions and/or variables you need here.

///
// This function loads texture data for the GPU.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
///
void loadTextures( void )
{
    // Add your code here.

	//the texture of tablecloth
	glActiveTexture(GL_TEXTURE0);//select OpenGL texture unit
	GLuint texture_unit1 = SOIL_load_OGL_texture("tablecloth.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_TEXTURE_REPEATS
	);

	//the texture of flower
	glActiveTexture(GL_TEXTURE2);//select OpenGL texture unit
	GLuint texture_unit2 = SOIL_load_OGL_texture("Flower.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_TEXTURE_REPEATS
	);
}

///
// This function sets up the parameters for texture use.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param obj - The object type of the object being drawn
///
void setUpTextures( GLuint program, int obj )
{
    // Add your code here.
	if (obj == 0) {
		//******************************** Bind textures to texture units *****************//
		glUseProgram(program);// Make the shader program active
		int index1 = glGetUniformLocation(program, "texture1");
		//******************************* Connect samplers to texture units ****************//
		glUniform1i(index1, 0);// Texture unit 0
		
	}

	if (obj == 10) {
		//******************************** Bind textures to texture units *****************//
		glUseProgram(program);// Make the shader program active
		int index1 = glGetUniformLocation(program, "texture1");
		//******************************* Connect samplers to texture units ****************//
		glUniform1i(index1, 2);// Texture unit 0

	}
}
