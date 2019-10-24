//
//  Pipeline.cpp
//
//  Created by Warren R. Carithers on 2016/10/19.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Last updated 2019/02/25 by wrc.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Wei Zeng
//

#include <iostream>
#include <math.h>

#include "Pipeline.h"




///
// Simple wrapper class for midterm assignment
//
// Only methods in the implementation file whose bodies
// contain the comment
//
//    // YOUR IMPLEMENTATION HERE
//
// are to be modified by students.
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///
Pipeline::Pipeline(int w, int h) : Canvas(w, h)
    // YOUR IMPLEMENTATION HERE if you need to add initializers
{
    // YOUR IMPLEMENTATION HERE if you need to modify the constructor
	
	
}

//********************* global variables **********************************
Vertex polyArr[1000][1000];//add polygons to the array
Vertex clipArr[1000][1000];//store polygons after clipping
Vertex viewArr[1000][1000];//store polygons after viewport transforming 
int numOfVertex[1000];//the number of vertexs of the polygon polyArr[ID]
int numOfClip[1000];//the number of vertexs of the polygon clipArr[ID]
int ID = 0;//the unique identifier of polygon 
float p[3][3];//the identity matrix
float bottom2, top2, left2, right2;// the boundaries of clip window



///
// addPoly - Add a polygon to the canvas.  This method does not draw
//           the polygon, but merely stores it for later drawing.
//           Drawing is initiated by the drawPoly() method.
//
//           Returns a unique integer id for the polygon.
//
// @param p - Array containing the vertices of the polygon to be added.
// @param n - Number of vertices in polygon
//
// @return a unique integer identifier for the polygon
///
int Pipeline::addPoly( const Vertex p[], int n )
{
    // YOUR IMPLEMENTATION HERE

    // REMEMBER TO RETURN A UNIQUE ID FOR THE POLYGON

	numOfVertex[ID] = n;
	for (int i = 0; i < n; i++) {
		polyArr[ID][i] = p[i];// add the polygon p[] to polyArr
	}
	ID++;
    return ID - 1;
}



///
// drawPoly - Draw the polygon with the given id.  The polygon should
//            be drawn after applying the current transformation to
//            the vertices of the polygon.
//
// @param polyID - the ID of the polygon to be drawn.
///
void Pipeline::drawPoly( int polyID )
{
    // YOUR IMPLEMENTATION HERE

	int n = numOfClip[polyID];// the number of vertexs of current polygon 
	int x[1000];
	int y[1000];
	for (int i = 0; i < n; i++) {
		Vertex tempVertex = viewArr[polyID][i];//view port is the last transform 
		//***multiplied by the matrix of current transform*********//
		x[i] =(int) (p[0][0] * tempVertex.x + p[0][1] * tempVertex.y + p[0][2] * 1);
		y[i] =(int) (p[1][0] * tempVertex.x + p[1][1] * tempVertex.y + p[1][2] * 1);
	}

	//*******************the implementation for assignment 2******************************************//
	//***************Define the structure of bucket(ET and AL)***********************//
	struct Edge {
		int y;//ymax
		float x;//x of the vertex with the ymin coordinate
		float m;//the x increment (1/ m)
		Edge *next = NULL;//a link to the next bucket
	};

	//*************** find ymin and ymax of the polygon***********************//
	int minY = 99999999, maxY = -99999999;
	for (int i = 0; i < n; i++) {
		if (y[i] > maxY) {
			maxY = y[i];
		}
		if (y[i] < minY) {
			minY = y[i];
		}
	}
	Edge *ET[1000];//Create the edge table(ET)
	//Initialize ET
	for (int i = minY; i <= maxY; i++) {
		ET[i] = new Edge;
		ET[i]->next = NULL;
	}
	//****************Transfer the coordinate points to ET bucket*******************//
	for (int i = 0; i < n; i++) {
		if (i != n - 1) {
			//0<= i <= n-2
			if (y[i] != y[i + 1]) {
				//edge(i, i+1) is not horizontal
				int tempMinY;//index of ET[]
				int tempMaxY;//ymax in bucket
				float tempXOfMinY;//x in bucket
				float tempSlope;//m in bucket
				if (y[i] > y[i + 1]) {
					//slope < 0
					tempMinY = y[i + 1];
					tempMaxY = y[i];
					tempXOfMinY = x[i + 1];
					tempSlope = (float)(x[i + 1] - x[i]) / (float)(y[i + 1] - y[i]);
				}
				else {
					//slope >= 0
					tempMinY = y[i];
					tempMaxY = y[i + 1];
					tempXOfMinY = x[i];
					tempSlope = (float)(x[i + 1] - x[i]) / (float)(y[i + 1] - y[i]);
				}
				Edge *edge = new Edge;
				edge->y = tempMaxY;
				edge->x = tempXOfMinY;
				edge->m = tempSlope;
				if (ET[tempMinY]->next == NULL) {
					ET[tempMinY]->next = edge;
				}
				else {
					Edge *temp = ET[tempMinY]->next;
					edge->next = temp;
					ET[tempMinY]->next = edge;
				}
			}
			else//edge(i, i+1) is horizontal, do not transfer the point, but draw the line immediately
			{
				int tempMax, tempMin;
				if (x[i] > x[i + 1]) {
					tempMax = x[i];
					tempMin = x[i + 1];
				}
				else
				{
					tempMax = x[i + 1];
					tempMin = x[i];
				}
				for (int j = tempMin; j <= tempMax; j++) {
					setPixel(j, y[i]);
		
				}
			}

		}
		else {//i = n -1, the last edge is (n-1, 0)
			if (y[n - 1] == y[0]) {
				int tempMax, tempMin;
				if (x[n - 1] > x[0]) {
					tempMax = x[n - 1];
					tempMin = x[0];
				}
				else
				{
					tempMax = x[0];
					tempMin = x[n - 1];
				}
				for (int j = tempMin; j <= tempMax; j++) {
					setPixel(j, y[0]);

				}
			}
			else {
				int tempMinY;
				int tempMaxY;
				float tempXOfMinY;
				float tempSlope;
				if (y[n - 1] > y[0]) {
					tempMinY = y[0];
					tempMaxY = y[n - 1];
					tempXOfMinY = x[0];
					tempSlope = (float)(x[0] - x[n - 1]) / (float)(y[0] - y[n - 1]);
				}
				else {
					tempMinY = y[n - 1];
					tempMaxY = y[0];
					tempXOfMinY = x[n - 1];
					tempSlope = (float)(x[0] - x[n - 1]) / (float)(y[0] - y[n - 1]);
				}
				Edge *edge = new Edge;
				edge->y = tempMaxY;
				edge->x = tempXOfMinY;
				edge->m = tempSlope;
				if (ET[tempMinY]->next == NULL) {
					ET[tempMinY]->next = edge;
				}
				else {
					Edge *temp = ET[tempMinY]->next;
					edge->next = temp;
					ET[tempMinY]->next = edge;
				}
			}
		}
	}
	Edge *AL = new Edge;
	AL->next = NULL;//Initialize the active list(AL) to empty
	for (int i = minY; i <= maxY; i++) {
		//set i to the index of the first non-empty bucket list
		//while there are still edges in ET

		//*****************Discard entries from AL where y = ymax = i ************************//
		Edge *tempAL = AL;
		Edge *temp = tempAL->next;
		while (temp) {
			if (temp->y == i) {
				tempAL->next = temp->next;
				temp = tempAL->next;
			}
			else {
				tempAL = tempAL->next;
				temp = tempAL->next;
			}
		}
		//**********According to x in buckets, insert all buckets from ET[i] to AL in order **********************//; 
		Edge *tempETEdge = ET[i]->next;
		Edge *tempALEdge = AL;
		while (tempETEdge) {
			while (tempALEdge->next && tempETEdge->x > tempALEdge->next->x) {
				tempALEdge = tempALEdge->next;
			}
			Edge *tempEdge = tempETEdge->next;
			tempETEdge->next = tempALEdge->next;
			tempALEdge->next = tempETEdge;
			tempETEdge = tempEdge;
			tempALEdge = AL;
		}

		//********************Fill pixels on scan line y using pairs of x coordinates from AL **************//
		Edge *tempALL = AL->next;
		while (tempALL && tempALL->next) {
			float min, max;
			if (tempALL->x > tempALL->next->x) {
				max = tempALL->x;
				min = tempALL->next->x;
			}
			else
			{
				max = tempALL->next->x;
				min = tempALL->x;
			}
			for (int j = min; j <= max; j++) {
				setPixel(j, i);
				
			}
			tempALL = tempALL->next->next;
		}

		//******************For each non-vertical edge in AL, add 1 / m to x *************************//
		Edge *tempAddEdge = AL->next;
		while (tempAddEdge) {
			tempAddEdge->x += tempAddEdge->m;
			tempAddEdge = tempAddEdge->next;
		}
	}
	//***********************The assignment2 ends *********************************************************//
}

///
// clearTransform - Set the current transformation to the identity matrix.
///
void Pipeline::clearTransform( void )
{
    // YOUR IMPLEMENTATION HERE

	//CM = {1 0 0
	//      0 1 0
	//      0 0 1}
	p[0][0] = 1;
	p[0][1] = 0;
	p[0][2] = 0;
	p[1][0] = 0;
	p[1][1] = 1;
	p[1][2] = 0;
	p[2][0] = 0;
	p[2][1] = 0;
	p[2][2] = 1;
}

///
// translate - Add a translation to the current transformation by
//             premultiplying the appropriate translation matrix to
//             the current transformation matrix.
//
// @param x - Amount of translation in x.
// @param y - Amount of translation in y.
///
void Pipeline::translate( float tx, float ty )
{
    // YOUR IMPLEMENTATION HERE

	//CM = T(x, y) * CM
	//T(x, y) = {1 0 tx
	//           0 1 ty
	//           0 0  1}
	p[0][0] = 1 * p[0][0] + 0 * p[1][0] + tx * p[2][0];
	p[0][1] = 1 * p[0][1] + 0 * p[1][1] + tx * p[2][1];
	p[0][2] = 1 * p[0][2] + 0 * p[1][2] + tx * p[2][2];

	p[1][0] = 0 * p[0][0] + 1 * p[1][0] + ty * p[2][0];
	p[1][1] = 0 * p[0][1] + 1 * p[1][1] + ty * p[2][1];
	p[1][2] = 0 * p[0][2] + 1 * p[1][2] + ty * p[2][2];

	p[2][0] = 0 * p[0][0] + 0 * p[1][0] + 1 * p[2][0];
	p[2][1] = 0 * p[0][1] + 0 * p[1][1] + 1 * p[2][1];
	p[2][2] = 0 * p[0][2] + 0 * p[1][2] + 1 * p[2][2];


}

///
// rotate - Add a rotation to the current transformation by premultiplying
//          the appropriate rotation matrix to the current transformation
//          matrix.
//
// @param degrees - Amount of rotation in degrees.
///
void Pipeline::rotate( float degrees )
{
    // YOUR IMPLEMENTATION HERE

	//CM = R(¦È) * CM
	//R(¦È) = { cos¦È -sin¦È 0
	//          sin¦È  cos¦È 0
	//            0      0   1}

	//¦È = degress * ¦Ð / 180
	p[0][0] = cos(degrees * 3.14 / 180) * p[0][0] + (-sin(degrees * 3.14 / 180) * p[1][0]) + 0 * p[2][0];
	p[0][1] = cos(degrees * 3.14 / 180) * p[0][1] + (-sin(degrees * 3.14 / 180) * p[1][1]) + 0 * p[2][1];
	p[0][2] = cos(degrees * 3.14 / 180) * p[0][2] + (-sin(degrees * 3.14 / 180) * p[1][2]) + 0 * p[2][2];

	p[1][0] = sin(degrees * 3.14 / 180) * p[0][0] + cos(degrees * 3.14 / 180) * p[1][0] + 0 * p[2][0];
	p[1][1] = sin(degrees * 3.14 / 180) * p[0][1] + cos(degrees * 3.14 / 180) * p[1][1] + 0 * p[2][1];
	p[1][2] = sin(degrees * 3.14 / 180) * p[0][2] + cos(degrees * 3.14 / 180) * p[1][2] + 0 * p[2][2];

	p[2][0] = 0 * p[0][0] + 0 * p[1][0] + 1 * p[2][0];
	p[2][1] = 0 * p[0][1] + 0 * p[1][1] + 1 * p[2][1];
	p[2][2] = 0 * p[0][2] + 0 * p[1][2] + 1 * p[2][2];

}

///
// scale - Add a scale to the current transformation by premultiplying
//         the appropriate scaling matrix to the current transformation
//         matrix.
//
// @param x - Amount of scaling in x.
// @param y - Amount of scaling in y.
///
void Pipeline::scale( float sx, float sy )
{
    // YOUR IMPLEMENTATION HERE

	//CM = S(x, y) * CM
	//S(x, y) = { sx 0  0
	//            0  sy 0
	//            0  0   1}
	p[0][0] = sx * p[0][0] + 0 * p[1][0] + 0 * p[2][0];
	p[0][1] = sx * p[0][1] + 0 * p[1][1] + 0 * p[2][1];
	p[0][2] = sx * p[0][2] + 0 * p[1][2] + 0 * p[2][2];

	p[1][0] = 0 * p[0][0] + sy * p[1][0] + 0 * p[2][0];
	p[1][1] = 0 * p[0][1] + sy * p[1][1] + 0 * p[2][1];
	p[1][2] = 0 * p[0][2] + sy * p[1][2] + 0 * p[2][2];

	p[2][0] = 0 * p[0][0] + 0 * p[1][0] + 1 * p[2][0];
	p[2][1] = 0 * p[0][1] + 0 * p[1][1] + 1 * p[2][1];
	p[2][2] = 0 * p[0][2] + 0 * p[1][2] + 1 * p[2][2];
}

///
// setClipWindow - Define the clip window.
//
// @param bottom - y coord of bottom edge of clip window (in world coords)
// @param top - y coord of top edge of clip window (in world coords)
// @param left - x coord of left edge of clip window (in world coords)
// @param right - x coord of right edge of clip window (in world coords)
///

//****************************The implementation of assignment3 ******************************************//
int clipPolygon(int in, const Vertex inV[], Vertex outV[],
	Vertex ll, Vertex ur)
{
	//***************************Upper Boundary*************************
	Vertex p = inV[in - 1];
	Vertex out1[50];
	int outLen1 = 0;
	for (int j = 0; j < in; j++) {
		Vertex s = inV[j];

		if (s.y < ur.y) {// Cases 1 & 4
			if (p.y < ur.y) {// Case 1
				out1[outLen1] = s;
				outLen1++;
			}
			else
			{// Case 4
				Vertex i;
				i.y = ur.y;
				if (p.x == s.x) {
					i.x = p.x;
				}
				else
				{
					float slope = (p.y - s.y) / (p.x - s.x);
					float b = p.y - slope * p.x;
					i.x = (i.y - b) / slope;
				}
				out1[outLen1] = i;
				outLen1++;
				out1[outLen1] = s;
				outLen1++;
			}
		}
		else
		{// Case 2 & 3
			if (p.y < ur.y) {// Case 2
				Vertex i;
				i.y = ur.y;
				if (p.x == s.x) {
					i.x = p.x;
				}
				else
				{
					float slope = (p.y - s.y) / (p.x - s.x);
					float b = p.y - slope * p.x;
					i.x = (i.y - b) / slope;
				}
				out1[outLen1] = i;
				outLen1++;
			}// Case 3 adds nothing
		}
		p = s;
	}

	//***************************Right Boundary*************************
	p = out1[outLen1 - 1];
	Vertex out2[50];
	int outLen2 = 0;
	for (int j = 0; j < outLen1; j++) {
		Vertex s = out1[j];

		if (s.x < ur.x) {
			if (p.x < ur.x) {
				out2[outLen2] = s;
				outLen2++;
			}
			else
			{
				Vertex i;
				i.x = ur.x;
				float slope = (p.y - s.y) / (p.x - s.x);
				float b = p.y - slope * p.x;
				i.y = slope * i.x + b;
				out2[outLen2] = i;
				outLen2++;
				out2[outLen2] = s;
				outLen2++;
			}
		}
		else
		{
			if (p.x < ur.x) {
				Vertex i;
				i.x = ur.x;
				float slope = (p.y - s.y) / (p.x - s.x);
				float b = p.y - slope * p.x;
				i.y = slope * i.x + b;
				out2[outLen2] = i;
				outLen2++;
			}
		}
		p = s;
	}

	//***************************Lower Boundary*************************
	p = out2[outLen2 - 1];
	Vertex out3[50];
	int outLen3 = 0;
	for (int j = 0; j < outLen2; j++) {
		Vertex s = out2[j];

		if (s.y > ll.y) {
			if (p.y > ll.y) {
				out3[outLen3] = s;
				outLen3++;
			}
			else
			{
				Vertex i;
				i.y = ll.y;
				if (p.x == s.x) {
					i.x = p.x;
				}
				else
				{
					float slope = (p.y - s.y) / (p.x - s.x);
					float b = p.y - slope * p.x;
					i.x = (i.y - b) / slope;
				}
				out3[outLen3] = i;
				outLen3++;
				out3[outLen3] = s;
				outLen3++;
			}
		}
		else
		{
			if (p.y > ll.y) {
				Vertex i;
				i.y = ll.y;
				if (p.x == s.x) {
					i.x = p.x;
				}
				else
				{
					float slope = (p.y - s.y) / (p.x - s.x);
					float b = p.y - slope * p.x;
					i.x = (i.y - b) / slope;
				}
				out3[outLen3] = i;
				outLen3++;
			}
		}
		p = s;
	}

	//***************************left Boundary*************************
	p = out3[outLen3 - 1];
	Vertex out4[50];
	int outLen4 = 0;
	for (int j = 0; j < outLen3; j++) {
		Vertex s = out3[j];

		if (s.x > ll.x) {
			if (p.x > ll.x) {
				out4[outLen4] = s;
				outLen4++;
			}
			else
			{
				Vertex i;
				i.x = ll.x;
				float slope = (p.y - s.y) / (p.x - s.x);
				float b = p.y - slope * p.x;
				i.y = slope * i.x + b;
				out4[outLen4] = i;
				outLen4++;
				out4[outLen4] = s;
				outLen4++;
			}
		}
		else
		{
			if (p.x > ll.x) {
				Vertex i;
				i.x = ll.x;
				float slope = (p.y - s.y) / (p.x - s.x);
				float b = p.y - slope * p.x;
				i.y = slope * i.x + b;
				out4[outLen4] = i;
				outLen4++;
			}
		}
		p = s;
	}

	//*************************** Output Array *************************
	for (int i = 0; i < outLen4; i++) {
		outV[i] = out4[i];
	}
	return(outLen4);  // remember to return the outgoing vertex count!
}

void Pipeline::setClipWindow( float bottom, float top, float left, float right )
{
    // YOUR IMPLEMENTATION HERE

	//ll(lfet, bottom)
	//ur(right, top)
	Vertex ll, ur;
	ll.x = left;
	ll.y = bottom;
	ur.x = right;
	ur.y = top;
	for (int i = 0; i < ID; i++) {
		Vertex outV[1000];
		numOfClip[i] = clipPolygon(numOfVertex[i], polyArr[i], outV, ll, ur);//clip the current plygon 
		for (int j = 0; j < numOfClip[i]; j++) {
			clipArr[i][j] = outV[j];//store outV[] to clipArr[]
		}
	}
	//store the boundaries 
	bottom2 = bottom;
	top2 = top;
	left2 = left;
	right2 = right;

}

///
// setViewport - Define the viewport.
//
// @param xmin - x coord of lower left of view window (in screen coords)
// @param ymin - y coord of lower left of view window (in screen coords)
// @param width - width of view window (in world coords)
// @param height - width of view window (in world coords)
///
void Pipeline::setViewport( int x, int y, int width, int height )
{
     // YOUR IMPLEMENTATION HERE

	//*********************************Transform directly from clip window **************************//
	//p = {x
	//     y
	//     1}

	//CM = {sx  0  tx
	//       0 sy  ty
	//       0  0  1}
	
	float sx = (x + width - x) / (right2 - left2);//sx = (xmax - xmin) / (right - left)
	float sy = (y + height - y) / (top2 - bottom2);//sy = (ymax - ymin) / (top - bottom)
	float tx = (right2 * x - left2 * (width + x)) / (right2 - left2);//tx = (right * xmin - left * xmax) / (right - left)
	float ty = (top2 * y - bottom2 * (y + height)) / (top2 - bottom2);//ty = (top * ymin - bottom * ymax) / (top - bottom)
	for (int i = 0; i < ID; i++) {
		for (int j = 0; j < numOfClip[i]; j++) {
			viewArr[i][j].x = sx * clipArr[i][j].x + 0 * clipArr[i][j].y + tx * 1;//x' = sx * x + 0 * y + tx * 1
			viewArr[i][j].y = 0 * clipArr[i][j].x + sy * clipArr[i][j].y + ty * 1;//y' = 0 * x + sy * y + ty * 1
		}
	}

}
