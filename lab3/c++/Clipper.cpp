//
//  Clipper.c
//
//  Created by Warren R. Carithers on 01/15/14.
//  Last updated 2019/02/16 by wrc.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  Wei Zeng
//

#ifdef __cplusplus
using namespace std;
#else
#include <stdbool.h>
#endif

#include "Vertex.h"
#include "Clipper.h"




///
// Simple module that performs clipping
///

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///



int clipPolygon( int in, const Vertex inV[], Vertex outV[],
		 Vertex ll, Vertex ur )
{
    // YOUR CODE GOES HERE

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


