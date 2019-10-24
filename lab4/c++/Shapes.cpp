///
//  Shapes.cpp
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  Author:  Warren R. Carithers 2017/04/01.
//  Last updated 2019/03/27.
//
//  Contributor: Wei Zeng
///

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"

///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions )
{
    if( subdivisions < 1 )
        subdivisions = 1;

    // YOUR IMPLEMENTATION HERE
	float x, y, z;
	float seg = 1.0 / (float) subdivisions;//the length of sides of triangle
	Vertex p1, p2, p3;

	//****************************************front face*******************************//
	x = -0.5;
	y = 0.5;
	z = 0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempY = y - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempX = x + j * seg;

			p1.x = tempX;
			p1.y = tempY;
			p1.z = z;//coordinate of z is same
			p2.x = tempX;
			p2.y = tempY - seg;
			p2.z = z;
			p3.x = tempX + seg;
			p3.y = tempY;
			p3.z = z;
			C.addTriangle(p1, p2, p3);//add vertices in counter-clickwise order

			p1.x = tempX;
			p1.y = tempY - seg;
			p1.z = z;
			p2.x = tempX + seg;
			p2.y = tempY - seg;
			p2.z = z;
			p3.x = tempX + seg;
			p3.y = tempY;
			p3.z = z;
			C.addTriangle(p1, p2, p3);
		}
	}

	//****************************************right face*******************************//
	x = 0.5;
	y = 0.5;
	z = 0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempY = y - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempZ = z - j * seg;

			p1.x = x;
			p1.y = tempY;
			p1.z = tempZ;
			p2.x = x;
			p2.y = tempY - seg;
			p2.z = tempZ;
			p3.x = x;
			p3.y = tempY;
			p3.z = tempZ - seg;
			C.addTriangle(p1, p2, p3);

			p1 = p2;
			p2.x = x;
			p2.y = tempY - seg;
			p2.z = tempZ - seg;
			C.addTriangle(p1, p2, p3);
		}
	}

	//****************************************back face*******************************//
	x = -0.5;
	y = 0.5;
	z = -0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempY = y - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempX = x + j * seg;

			p1.x = tempX;
			p1.y = tempY;
			p1.z = z;
			p2.x = tempX;
			p2.y = tempY - seg;
			p2.z = z;
			p3.x = tempX + seg;
			p3.y = tempY;
			p3.z = z;
			C.addTriangle(p1, p2, p3);

			p1.x = tempX;
			p1.y = tempY - seg;
			p1.z = z;
			p2.x = tempX + seg;
			p2.y = tempY - seg;
			p2.z = z;
			p3.x = tempX + seg;
			p3.y = tempY;
			p3.z = z;
			C.addTriangle(p1, p2, p3);
		}
	}

	//****************************************left face*******************************//
	x = -0.5;
	y = 0.5;
	z = 0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempY = y - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempZ = z - j * seg;

			p1.x = x;
			p1.y = tempY;
			p1.z = tempZ;
			p2.x = x;
			p2.y = tempY - seg;
			p2.z = tempZ;
			p3.x = x;
			p3.y = tempY;
			p3.z = tempZ - seg;
			C.addTriangle(p1, p2, p3);

			p1 = p2;
			p2.x = x;
			p2.y = tempY - seg;
			p2.z = tempZ - seg;
			C.addTriangle(p1, p2, p3);
		}
	}

	//****************************************top face*******************************//
	x = 0.5;
	y = 0.5;
	z = 0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempX = x - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempZ = z - j * seg;

			p1.x = tempX;
			p1.y = y;
			p1.z = tempZ;
			p2.x = tempX;
			p2.y = y;
			p2.z = tempZ - seg;
			p3.x = tempX - seg;
			p3.y = y;
			p3.z = tempZ;
			C.addTriangle(p1, p2, p3);

			p1 = p3;
			p3.x = tempX - seg;
			p3.y = y;
			p3.z = tempZ -seg;
			C.addTriangle(p1, p2, p3);
		}
	}
	
	//****************************************bottom face*******************************//
	x = 0.5;
	y = -0.5;
	z = 0.5;
	for (int i = 0; i < subdivisions; i++) {
		float tempX = x - i * seg;
		for (int j = 0; j < subdivisions; j++) {
			float tempZ = z - j * seg;

			p1.x = tempX;
			p1.y = y;
			p1.z = tempZ;
			p2.x = tempX;
			p2.y = y;
			p2.z = tempZ - seg;
			p3.x = tempX - seg;
			p3.y = y;
			p3.z = tempZ;
			C.addTriangle(p1, p2, p3);

			p1 = p3;
			p3.x = tempX - seg;
			p3.y = y;
			p3.z = tempZ - seg;
			C.addTriangle(p1, p2, p3);
		}
	}
}

///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius,
                   int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE
	double angle = 2 * 3.141592653 / (double)radialDivisions;//the angle of each triangle 
	float height = 1.0 / (float)heightDivisions;//the height of each subvision
	Vertex p0, p1, p2, p3, p4;
	p0.x = 0;
	p0.z = 0;
	p1.x = radius;
	p1.z = 0;

	for (int i = 0; i < radialDivisions; i++) {
		p0.y = 0.5;
		p1.y = 0.5;
		p2.y = 0.5;
		p2.x = (float)(radius * cos(angle * (i + 1)));//x = cos(a)
		p2.z = (float)(radius * sin(angle * (i + 1)));//z = sin(a)
		C.addTriangle(p0, p1, p2);//top circle

		p0.y = -0.5;
		p1.y = -0.5;
		p2.y = -0.5;
		C.addTriangle(p0, p1, p2);//bottom circle

		for (int j = 0; j < heightDivisions; j++) {
			p1.y = -0.5 + height * j;
			p2.y = -0.5 + height * j;

			p3.x = p1.x;
			p3.y = p1.y + height;
			p3.z = p1.z;
			C.addTriangle(p1, p2, p3);//side face

			p4.x = p2.x;
			p4.y = p2.y * j + height;
			p4.z = p2.z;
			C.addTriangle(p2, p4, p4);//side face
		}

		p1.x = p2.x;
		p1.z = p2.z;

	}
	

}

///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius,
               int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE
	double angle = 2 * 3.141592653 / (double)radialDivisions;//the angle of each triangle
	float height = 1.0 / (float)heightDivisions;//the height of each subvision
	float rad = 0.5 / (float)heightDivisions;//the decrease of radius
	Vertex p0, p1, p2, p3, p4;
	Vertex p11, p22;

	p0.x = 0;
	p0.z = 0;
	p1.x = radius;
	p1.z = 0;
	p4.x = p1.x - rad;
	p4.z = p1.z;

	for (int i = 0; i < radialDivisions; i++) {
		p0.y = -0.5;
		p1.y = -0.5;
		p2.y = -0.5;
		p2.x = (float)(radius * cos(angle * (i + 1)));//x = cos(a)
		p2.z = (float)(radius * sin(angle * (i + 1)));//z = sin(a)
		C.addTriangle(p0, p1, p2);//bottom circle

		p11.x = p1.x;
		p11.z = p1.z;
		p22.x = p2.x;
		p22.z = p2.z;

		for (int j = 0; j < heightDivisions; j++) {
			p11.y = -0.5 + height * j;
			p22.y = -0.5 + height * j;
			p3.x = (float)((radius - rad * (j + 1))* cos(angle * (i + 1)));//decrease of x
			p3.y = p11.y + height;
			p3.z = (float)((radius - rad * (j + 1))* sin(angle * (i + 1)));//decrease of z
			p4.x = (float)((radius - rad * (j + 1))* cos(angle * (i)));//decrease of x
			p4.y = p22.y + height;
			p4.z = (float)((radius - rad * (j + 1))* sin(angle * (i)));//decrease of z
			C.addTriangle(p11, p4, p22);//side face
			C.addTriangle(p22, p4, p3);//side face
			p11.x = p4.x;
			p11.z = p4.z;
			p22.x = p3.x;
			p22.z = p3.z;
		}

		p1.x = p2.x;
		p1.z = p2.z;

	}
}

///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use only the "slices" parameter
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5

    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;
    
    // YOUR IMPLEMENTATION HERE
	double angleLa = 2.0 * 3.141592653 / (double)slices;//the latitude angle 
	double angleLo = 3.141592653 / (double)stacks;//the longitude angle
	Vertex p1, p2, p3, p4;
	Vertex p11, p22;
	float R, Y, tempR, tempY;

	//*************************************odd stack***************************************//
	if (stacks % 2 != 0)
	{
		//*************************************top layer***************************************//
		R = (float)(radius * cos(angleLo / 2));//the longitude radius = r * cos(the longitude angle)
		Y = (float)(radius * sin(angleLo / 2));//the y coordinate = r * sin(the longitude angle)
		p1.x = R;
		p1.z = 0;
		for (int i = 0; i < stacks / 2; i++) {
			tempR = (float)(radius * cos((angleLo * (i + 1)) + angleLo / 2));//the radius of new longitude
			tempY = (float)(radius * sin((angleLo * (i + 1)) + angleLo / 2));//the y coordinate of new longitude

			for (int j = 0; j < slices; j++) {
				p2.x = (float)(R * cos(angleLa * (j + 1)));
				p2.z = (float)(R * sin(angleLa * (j + 1)));

				p11.x = p1.x;
				p11.y = Y;
				p11.z = p1.z;
				p22.x = p2.x;
				p22.y = Y;
				p22.z = p2.z;

				p3.x = (float)(tempR * cos(angleLa * (j + 1)));
				p3.y = tempY;
				p3.z = (float)(tempR * sin(angleLa * (j + 1)));
				p4.x = (float)(tempR * cos(angleLa * (j)));
				p4.y = tempY;
				p4.x = (float)(tempR * sin(angleLa * (j)));

				C.addTriangle(p11, p4, p22);
				C.addTriangle(p22, p4, p3);

				p1.x = p2.x;
				p1.z = p2.z;
			}
			p1.x = tempR;
			p1.z = 0;
			Y = tempY;
			R = tempR;
		}

		//*************************************middle layer***************************************//
		R = (float)(radius * cos(-angleLo / 2));
		Y = (float)(radius * sin(-angleLo / 2));
		tempR = (float)(radius * cos(angleLo / 2));
		tempY = (float)(radius * sin(angleLo / 2));
		p1.x = R;
		p1.z = 0;
		p11.x = p1.x;
		p11.z = p1.z;
		for (int i = 0; i < slices; i++) {
			p2.x = (float)(R * cos(angleLa * (i + 1)));
			p2.z = (float)(R * sin(angleLa * (i + 1)));

			p11.x = p1.x;
			p11.y = Y;
			p11.z = p1.z;
			p22.x = p2.x;
			p22.y = Y;
			p22.z = p2.z;

			p3.x = (float)(tempR * cos(angleLa * (i + 1)));
			p3.y = tempY;
			p3.z = (float)(tempR * sin(angleLa * (i + 1)));
			p4.x = (float)(tempR * cos(angleLa * (i)));
			p4.y = tempY;
			p4.z = (float)(tempR * sin(angleLa * (i)));

			C.addTriangle(p11, p4, p22);
			C.addTriangle(p22, p4, p3);

			p1.x = p2.x;
			p1.z = p2.z;
		}

		//*************************************bottom layer***************************************//
		R = (float)(radius * cos(-angleLo / 2));
		Y = (float)(radius * sin(-angleLo / 2));
		p1.x = R;
		p1.z = 0;
		p11.x = p1.x;
		p11.z = p1.z;
		for (int i = 0; i < stacks / 2; i++) {
			tempR = (float)(radius * cos(-((angleLo * (i + 1)) + angleLo / 2)));
			tempY = (float)(radius * sin(-((angleLo * (i + 1)) + angleLo / 2)));

			for (int j = 0; j < slices; j++) {
				p2.x = (float)(R * cos(angleLa * (j + 1)));
				p2.z = (float)(R * sin(angleLa * (j + 1)));

				p11.x = p1.x;
				p11.y = Y;
				p11.z = p1.z;
				p22.x = p2.x;
				p22.y = Y;
				p22.z = p2.z;

				p3.x = (float)(tempR * cos(angleLa * (j + 1)));
				p3.y = tempY;
				p3.z = (float)(tempR * sin(angleLa * (j + 1)));
				p4.x = (float)(tempR * cos(angleLa * (j)));
				p4.y = tempY;
				p4.x = (float)(tempR * sin(angleLa * (j)));
				C.addTriangle(p11, p3, p4);
				C.addTriangle(p11, p22, p3);

				p1.x = p2.x;
				p1.z = p2.z;
			}
			p1.x = tempR;
			p1.z = 0;
			Y = tempY;
			R = tempR;
		}
	}
    
	//*************************************even stack***************************************//
	if (stacks % 2 == 0) {
		//*************************************top layer***************************************//
		R = radius;
		Y = 0;
		p1.x = 0.5;
		p1.z = 0;
		for (int i = 0; i < stacks / 2; i++) {
			tempR = (float)(radius * cos(angleLo * (i + 1)));
			tempY = (float)(radius * sin(angleLo * (i + 1)));

			for (int j = 0; j < slices; j++) {
				p2.x = (float)(R * cos(angleLa * (j + 1)));
				p2.z = (float)(R * sin(angleLa * (j + 1)));

				p11.x = p1.x;
				p11.y = Y;
				p11.z = p1.z;
				p22.x = p2.x;
				p22.y = Y;
				p22.z = p2.z;

				p3.x = (float)(tempR * cos(angleLa * (j + 1)));
				p3.y = tempY;
				p3.z = (float)(tempR * sin(angleLa * (j + 1)));
				p4.x = (float)(tempR * cos(angleLa * (j)));
				p4.y = tempY;
				p4.z = (float)(tempR * sin(angleLa * (j)));

				C.addTriangle(p11, p4, p22);
				C.addTriangle(p22, p4, p3);

				p1.x = p2.x;
				p1.z = p2.z;
			}
			p1.x = tempR;
			p1.z = 0;
			Y = tempY;
			R = tempR;
		}

		//*************************************bottom layer***************************************//
		R = radius;
		Y = 0;
		p1.x = R;
		p1.z = 0;
		p11.x = p1.x;
		p11.z = p1.z;
		for (int i = 0; i < stacks / 2; i++) {
			tempR = (float)(radius * cos(-angleLo * (i + 1)));
			tempY = (float)(radius * sin(-angleLo * (i + 1)));

			for (int j = 0; j < slices; j++) {
				p2.x = (float)(R * cos(angleLa * (j + 1)));
				p2.z = (float)(R * sin(angleLa * (j + 1)));

				p11.x = p1.x;
				p11.y = Y;
				p11.z = p1.z;
				p22.x = p2.x;
				p22.y = Y;
				p22.z = p2.z;

				p3.x = (float)(tempR * cos(angleLa * (j + 1)));
				p3.y = tempY;
				p3.z = (float)(tempR * sin(angleLa * (j + 1)));
				p4.x = (float)(tempR * cos(angleLa * (j)));
				p4.y = tempY;
				p4.z = (float)(tempR * sin(angleLa * (j)));

				C.addTriangle(p11, p3, p4);
				C.addTriangle(p11, p22, p3);

				p1.x = p2.x;
				p1.z = p2.z;
			}
			p1.x = tempR;
			p1.z = 0;
			Y = tempY;
			R = tempR;
		}
	}
}
