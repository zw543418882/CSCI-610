///
//  Lighting
//
//  Simple module for setting up Phong illumination/shading.
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Last updated 2019/04/13 by wrc.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Wei Zeng
//
//  This code can be compiled as either C or C++.
///

#include "Lighting.h"
#include "Shapes.h"

// Add any global definitions and/or variables you need here.

///
// This function sets up the lighting, material, and shading parameters
// for the Phong shader.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param obj - The object type of the object being drawn
///
void setUpPhong(GLuint program, int obj)
{
	// Add your code here
	//***************send lighting parameters to the shader****************************//
	GLfloat light_source_position[] = { -2.0f, 1.0f, 15.0f, 1.0 };
	GLfloat light_source_color[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient_light_color[] = { 0.5, 0.5, 0.5, 1.0 };

	int indexLP = glGetUniformLocation(program, "light_source_position");
	int indexLC = glGetUniformLocation(program, "light_source_color");
	int indexAC = glGetUniformLocation(program, "ambient_light_color");

	glUniform4fv(indexLP, 1, light_source_position);
	glUniform4fv(indexLC, 1, light_source_color);
	glUniform4fv(indexAC, 1, ambient_light_color);
	//*********************************End**************************//

	if (obj == 0) {
		//*****************send quad parameters *********************//
		float ka = 0.7;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.7;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float specEx = 40.0;
		int indexSE = glGetUniformLocation(program, "se");
		glUniform1f(indexSE, specEx);
	}

	if (obj == 1) {
		//*****************send teapot parameters *********************//
		GLfloat ambient_mc[] = { 0.9, 0.9, 0.9, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 0.9, 0.9, 0.9, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat specular_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, specular_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.7;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 10.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);
	}

	if (obj == 2) {
		//*****************send sphere parameters *********************//
		GLfloat ambient_mc[] = { 1.0, 0.1, 0.0, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 1.0, 0.0, 0.0, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.8;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 3) {
		//*****************send vase parameters *********************//
		GLfloat ambient_mc[] = { 1.0, 1.0, 1.0, 0.2 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 1.0, 1.0, 1.0, 0.2 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.8;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 4) {
		//*****************send STICK parameters *********************//
		GLfloat ambient_mc[] = { 0.65, 0.25, 0.07, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 1.0, 0.5, 0.2, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.3;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 0.2;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 5) {
		//*****************send CANDLE parameters *********************//
		GLfloat ambient_mc[] = { 0.2, 0.5, 1.0, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 0.2, 0.5, 1.0, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.8;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 7) {
		//*****************send CUP parameters *********************//
		GLfloat ambient_mc[] = { 2.0, 2.0, 2.0, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 0.8, 0.8, 0.8, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.8;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 8) {
		//*****************send PLATE parameters *********************//
		GLfloat ambient_mc[] = { 3.0, 3.0, 3.0, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 3.0, 3.0, 3.0, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.5;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.8;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 1.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

	if (obj == 9) {
		//*****************send CAKE parameters *********************//
		GLfloat ambient_mc[] = { 1.2, 0.2, 0.06, 1.0 };
		int indexAMC = glGetUniformLocation(program, "amc");
		glUniform4fv(indexAMC, 1, ambient_mc);

		GLfloat diffuse_mc[] = { 1.0, 0.5, 0.2, 1.0 };
		int indexDMC = glGetUniformLocation(program, "dmc");
		glUniform4fv(indexDMC, 1, diffuse_mc);

		GLfloat spec_mc[] = { 1.0, 1.0, 1.0, 1.0 };
		int indexSMC = glGetUniformLocation(program, "smc");
		glUniform4fv(indexSMC, 1, spec_mc);

		float ka = 0.4;
		int indexKa = glGetUniformLocation(program, "ka");
		glUniform1f(indexKa, ka);

		float kd = 0.7;
		int indexKd = glGetUniformLocation(program, "kd");
		glUniform1f(indexKd, kd);

		float ks = 0.0;
		int indexKs = glGetUniformLocation(program, "ks");
		glUniform1f(indexKs, ks);

		float se = 50.0;
		int indexSe = glGetUniformLocation(program, "se");
		glUniform1f(indexSe, se);

	}

}
