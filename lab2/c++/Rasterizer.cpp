//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Last update 02/09/2019 by wrc.
//  Copyright 2018 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Wei Zeng
//

#include <list>
#include <algorithm>
#include <iostream>

#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Simple class that performs rasterization algorithms
///

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls to the
// setPixel() function.
//
// @param n - number of vertices
// @param x - array of x coordinates
// @param y - array of y coordinates
///
void Rasterizer::drawPolygon(int n, const int x[], const int y[] )
{
    // YOUR IMPLEMENTATION HERE

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
		if(y[i] > maxY) {
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
					C.setPixel(j, y[i]);
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
					C.setPixel(j, y[0]);
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
			while (tempALEdge->next && tempETEdge->x > tempALEdge->next->x){
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
				C.setPixel(j, i);
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
}



 


