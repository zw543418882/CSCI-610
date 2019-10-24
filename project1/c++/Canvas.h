//
//  Canvas.h
//
//  Created by Warren R. Carithers 2016/09/30.
//  Based on a C++ version created by Joe Geigel.
//  Last updated 2019/02/26 by wrc.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  Prototypes for routines for manipulating a simple canvas
//  holding point information along with color data.
//
//  This file should not be modified by students.
//

#ifndef _CANVAS_H_
#define _CANVAS_H_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Color.h"
#include "Vertex.h"

using namespace std;

#include <vector>

///
// Simple canvas class that allows for pixel-by-pixel rendering.
///

class Canvas {

    ///
    // canvas size information
    ///
    int width;
    int height;

    ///
    // point-related data
    ///

    // vertex locations
    vector<float> points;
    float *pointArray;

    // associated normal vectors
    vector<float> normals;
    float *normalArray;

    // associated (u,v) coordinates
    vector<float> uv;
    float *uvArray;

    // associated color data
    vector<float> colors;
    float *colorArray;

    // element count and connectivity data
    int numElements;
    GLuint *elemArray;

    ///
    // other Canvas defaults
    ///

    // current drawing color
    Color currentColor;

    // drawing depth
    float currentDepth;

public:

    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    Canvas( int w, int h );

    ///
    // Destructor
    ///
    ~Canvas( void );

    ///
    // clears the canvas
    ///
    void clear( void );

    ///
    // set the pixel Z coordinate
    //
    // @param d The depth to use
    //
    // @return  The old depth value
    ///
    float setDepth( float d );

    ///
    // Sets the current color
    //
    // @param c The new color
    ///
    void setColor( Color c );

    ///
    // writes a pixel using the current color
    //
    // @param x The x coord of the pixel to be set
    // @param y The y coord of the pixel to be set
    ///
    void setPixel( float x, float y );

    ///
    // writes a pixel using the specified color
    //
    // @param x The x coord of the pixel to be set
    // @param y The y coord of the pixel to be set
    // @param c The color to use
    ///
    void setPixelColor( float x, float y, Color c );

    ///
    // retrieve the array of element data from this Canvas
    ///
    GLuint *getElements( void );

    ///
    // retrieve the array of vertex data from this Canvas
    ///
    float *getVertices( void );

    ///
    // retrieve the array of normal data from this Canvas
    ///
    float *getNormals( void );

    ///
    // retrieve the array of (u,v) data from this Canvas
    ///
    float *getUV( void );

    ///
    // retrieve the array of color data from this Canvas
    ///
    float *getColors( void );

    ///
    // retrieve the vertex count from this Canvas
    ///
    int numVertices( void );

    ///
    // Assignment-specific additions to Canvas
    ///

    ///
    // Data members
    ///

    ///
    // outline vs. polygon drawing variables
    //
    // these are public to facilitate use by the driver program
    ///
    bool drawingOutlines;
    int countNum;
    const int countNumLimit;
    int *outlineCounts;

    ///
    // Member functions
    ///

    ///
    // Draw the outline of a polygon.
    //
    // Use this drawOutline() method only if you were NOT able to
    // create a working drawPolygon() Rasterizer routine of your own.
    // This method will only draw the outline of the polygon.
    //
    // @param n The number of vertices in the polygon
    // @param v The vertices that form the polygon
    ///
    void drawOutline( int n, const Vertex v[] );

    ///
    // Return the outline status of this object
    ///
    bool isOutline( void );

};

#endif
