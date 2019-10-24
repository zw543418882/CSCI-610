//
//  Rasterizer.cpp
//
//  Created by Warren R. Carithers on 01/28/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Wei Zeng
//

#include <cmath>

#include "Rasterizer.h"

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
// @param C the Canvas to be used
///

Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}


///
// Draw my initials
//
// Draw my own initials using calls to drawLine(), in the same
// manner that makeLines() in the driver program draws 'CG'.
///

void Rasterizer::myInitials( void ) {

    // ######## Use light blue (0.678,0.847,0.902) for initials ######## 

    C.setColor( 0.678, 0.847, 0.902 );

    //
    // add code here to draw your initials
    // with calls to your drawLine() function
    // 

	// ######## The letter 'W' in blue ########
	drawLine(40, 260, 80, 100);
	drawLine(80, 100, 140, 260);
	drawLine(140, 260, 200, 100);
	drawLine(200, 100, 240, 260);
	drawLine(40, 260, 50, 260);// Horizontal left to right
	drawLine(50, 260, 80, 120);
	drawLine(80, 120, 140, 270);
	drawLine(140, 270, 200, 120);
	drawLine(200, 120, 230, 260);
	drawLine(230, 260, 240, 260);// Horizontal left to right

	// ######## The letter 'Z' in blue ########
	drawLine(380, 260, 520, 260);// Horizontal left to right
	drawLine(520, 260, 400, 100);
	drawLine(400, 100, 540, 100);// Horizontal left to right
	drawLine(380, 260, 390, 270);
	drawLine(390, 270, 540, 270);// Horizontal left to right
	drawLine(540, 270, 420, 110);
	drawLine(420, 110, 550, 110);// Horizontal left to right
	drawLine(550, 110, 540, 100);

}

///
// Draw a line from (x0,y0) to (x1, y1)
//
// Implementation should be using the Midpoint Line Algorithm.
//
// You are to add the implementation here using only calls to the
// setPixel() method of the Canvas.
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
///

void Rasterizer::drawLine( int x0, int y0, int x1, int y1 )
{
    //
    // add code here to implement drawLine()
    // using the midpoint line algorithm
    //
	
	//To gurantee the line will be drawn from left to right
	//if the end point (x1, y1) is on the left of the end point(x0, x1), exchange their coordinates
	if (x0 > x1) {
		int temp0 = x0;
		int temp1 = y0;
		x0 = x1;
		y0 = y1;
		x1 = temp0;
		y1 = temp1;
	}

	
	int dx = x1 - x0, dy = y1 - y0;
	

	if (dx == 0) {
		//draw the vertical line
		//if y1 < y0, for(y = y0; y <= y1; y++) will be wrong
		//so we need to find the smaller value between y0 and y1
		int minY, maxY;
		if (y1 > y0) {
			minY = y0;
			maxY = y1;
		}
		else {
			minY = y1;
			maxY = y0;
		}

		for (int y = minY; y <= maxY; y++) {
			C.setPixel(x1, y);
		}
	}else if (dy == 0) {
		//draw the horizontal line
		for (int x = x0; x <= x1; x++) {
			C.setPixel(x, y0);
		}
	}
	else {
		float slope = (float)dy / (float)dx;
		

		if (slope <= 1 && slope > 0) {
			int dE, dNE, x, y, d;
			dE = 2 * dy;//delta if we choose E
			dNE = 2 * (dy - dx);//delta if we choose NE
			d = dE - dx;//initial d

			for (x = x0, y = y0; x <= x1; ++x) {
				C.setPixel(x, y);

				if (d <= 0) {
					d += dE;//choose E
				}
				else {
					y++;
					d += dNE;//choose NE
				}
			}
		}
		else if (slope > 1) {
			int dN, dNE, x, y, d;

			dN = -2 * dx;
			dNE = 2 * (dy - dx);
			d = dy - 2 * dx;

			for (x = x0, y = y0; y <= y1; y++) {
				C.setPixel(x, y);

				if (d <= 0) {
					d += dNE;
					x++;
				}
				else {
					d += dN;
				}
			}
			
		}
		else if (slope < 0 && slope >= -1) {
			int dE, dSE, x, y, d;

			dE = 2 * dy;
			dSE = 2 * (dy + dx);
			d = 2 * dy + dx;

			for (x = x0, y = y0; x < x1; x++) {
				C.setPixel(x, y);

				if (d <= 0) {
					d += dSE;
					y--;
				}
				else {
					d += dE;
				}
			}
		}
		else if (slope < -1) {
			int dS, dSE, x, y, d;

			dS = 2 * dx;
			dSE = 2 * (dy + dx);
			d = dy + 2 * dx;

			for (x = x0, y = y0; y >= y1; y--) {
				C.setPixel(x, y);

				if (d <= 0) {
					d += dS;
				}
				else {
					d += dSE;
					x++;
				}
			}
		}

	}
	

	


	
	

	

}
