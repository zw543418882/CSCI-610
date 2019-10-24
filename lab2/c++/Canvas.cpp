///
//  Canvas.cpp
//
//  Created by Warren R. Carithers 2016/09/30.
//  Based on a C++ version created by Joe Geigel.
//  Updates 2018/11/29 by wrc.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Routines for adding points to create a new mesh.
//
//  This file should not be modified by students.
///

#include <cstdlib>
#include <iostream>
#include <iomanip>

// Canvas.h includes all the OpenGL/GLFW/etc. header files for us
#include "Canvas.h"

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

Canvas::Canvas( int w, int h ) : width(w), height(h) {
    currentColor[0] = 0.0f;
    currentColor[1] = 0.0f;
    currentColor[2] = 0.0f;
    pointArray = 0;
    colorArray = 0;
    normalArray = 0;
    uvArray = 0;
    elemArray = 0;
    numElements = 0;
}

///
// Destructor
///

Canvas::~Canvas( void ) {
    clear();
}

///
// clear the canvas
//
// @param C The Canvas to use
///
void Canvas::clear( void )
{
    if( pointArray ) {
        delete [] pointArray;
        pointArray = 0;
    }
    if( normalArray ) {
        delete [] normalArray;
        normalArray = 0;
    }
    if( uvArray ) {
        delete [] uvArray;
        uvArray = 0;
    }
    if( elemArray ) {
        delete [] elemArray;
        elemArray = 0;
    }
    if( colorArray ) {
        delete [] colorArray;
        colorArray = 0;
    }
    points.clear();
    normals.clear();
    uv.clear();
    colors.clear();
    numElements = 0;
    currentColor[0] = 0.0;
    currentColor[1] = 0.0;
    currentColor[2] = 0.0;
}

///
// change the current drawing color
//
// @param r The red component of the new color (between 0-1)
// @param g The green component of the new color (between 0-1)
// @param b The blue component of the new color (between 0-1);
///
void Canvas::setColor( float r, float g, float b )
{
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
}

///
// set a pixel to the current drawing color
//
// @param x The x coord of the pixel to be set
// @param y The y coord of the pixel to be set
///
void Canvas::setPixel( int x0, int y0 )
{
    points.push_back( (float) x0 );
    points.push_back( (float) y0 );
    points.push_back( -1.0 );  // fixed Z depth
    points.push_back( 1.0 );

    colors.push_back( currentColor[0] );
    colors.push_back( currentColor[1] );
    colors.push_back( currentColor[2] );
    colors.push_back( 1.0 );   // alpha channel

    numElements += 1;
}

///
// gets the array of vertices for the current shape
///
float *Canvas::getVertices( void )
{
    // delete the old point array if we have one
    if( pointArray ) {
        delete [] pointArray;
        pointArray = 0;
    }

    int n = points.size();

    if( n > 0 ) {
        // create and fill a new point array
        pointArray = new float[ n ];
        if( pointArray == 0 ) {
            cerr << "point allocation failure" << endl;
            exit( 1 );
        }
        for( int i = 0; i < n; i++ ) {
            pointArray[i] = points[i];
        }
    }

    return pointArray;
}

///
// gets the array of normals for the current shape
///
float *Canvas::getNormals( void )
{
    // delete the old normal array if we have one
    if( normalArray ) {
        delete [] normalArray;
        normalArray = 0;
    }

    int n = normals.size();

    if( n > 0 ) {
        // create and fill a new normal array
        normalArray = new float[ n ];
        if( normalArray == 0 ) {
            cerr << "normal allocation failure" << endl;
            exit( 1 );
        }
        for( int i = 0; i < n; i++ ) {
            normalArray[i] = normals[i];
        }
    }

    return normalArray;
}

///
// gets the array of texture coordinates for the current shape
///
float *Canvas::getUV( void )
{
    // delete the old texture coordinate array if we have one
    if( uvArray ) {
        delete [] uvArray;
        uvArray = 0;
    }

    int n = uv.size();

    if( n > 0 ) {
        // create and fill a new texture coordinate array
        uvArray = new float[ n ];
        if( uvArray == 0 ) {
            cerr << "uv allocation failure" << endl;
            exit( 1 );
        }
        for( int i = 0; i < n; i++ ) {
            uvArray[i] = uv[i];
        }
    }

    return uvArray;
}

///
// gets the array of elements for the current shape
///
GLuint *Canvas::getElements( void )
{
    // delete the old element array if we have one
    if( elemArray ) {
        delete [] elemArray;
        elemArray = 0;
    }

    int n = numElements;

    if( n > 0 ) {
        // create and fill a new element array
        elemArray = new GLuint[ n ];
        if( elemArray == 0 ) {
            cerr << "element allocation failure" << endl;
            exit( 1 );
        }
        for( int i = 0; i < n; i++ ) {
            elemArray[i] = i;
        }
    }

    return elemArray;
}

///
// gets the array of colors for the current shape
///
float *Canvas::getColors( void )
{
    // delete the old color array if we have one
    if( colorArray ) {
        delete [] colorArray;
        colorArray = 0;
    }

    int n = colors.size();

    if( n > 0 ) {
        // create and fill a new color array
        colorArray = new float[ n ];
        if( colorArray == 0 ) {
            cerr << "color allocation failure" << endl;
            exit( 1 );
        }
        for( int i = 0; i < n; i++ ) {
            colorArray[i] = colors[i];
        }
    }

    return colorArray;
}

///
// returns number of vertices in current shape
///
int Canvas::numVertices( void )
{
    return numElements;
}
