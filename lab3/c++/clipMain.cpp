//
//  clipMain.cpp
//
//  Main program for polygon clip assignment
//
//  Created by Warren R. Carithers on 02/27/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "ShaderSetup.h"
#include "Vertex.h"
#include "Color.h"
#include "Buffers.h"
#include "Canvas.h"
#include "Clipper.h"

using namespace std;

///
// Object information
///

// our clipping regions (LL and UR corners)

Vertex regions[][2] = {
    { {  20, 120 }, {  70, 170 } },
    { {  30,  30 }, {  70,  80 } },
    { { 100,  34 }, { 130,  60 } },
    { {  90,  90 }, { 130, 120 } },
    { { 198, 198 }, { 276, 258 } },
    { { 221,  80 }, { 251, 101 } },
    { {  30, 200 }, {  90, 260 } }
};
int n_regions = sizeof(regions) / (2 * sizeof(Vertex));

///
// our polygons (list of vertices)
///

// quads, clipping region 1
// shades of red

Vertex quad1[] = {  // entirely inside the region
    {  35, 135 }, {  35, 155 }, {  55, 155 }, {  55, 135 }
};
int quad1_nv = sizeof(quad1) / sizeof(Vertex);
Color quad1c = { 1.00f, 0.00f, 0.00f, 1.00f };  // 0xFF0000

Vertex quad2[] = {  // entirely outside the region
    { 130, 140 }, { 130, 170 }, {  90, 170 }, {  90, 140 }
};
int quad2_nv = sizeof(quad2) / sizeof(Vertex);
Color quad2c = { 1.00f, 0.40f, 0.40f, 1.00f };  // 0xFF6666

// quads, clipping region 2
// shades of blue

Vertex quad3[] = {  // two vertices outside w/r/t the right edge
    {  64,  47 }, {  80,  47 }, {  80,  71 }, {  64,  71 }
};
int quad3_nv = sizeof(quad3) / sizeof(Vertex);
Color quad3c = { 0.00f, 0.45f, 0.60f, 1.00f };  // 0x0073FF

Vertex quad4[] = {  // two vertices outside w/r/t the left edge
    {  20,  60 }, {  50,  60 }, {  50,  50 }, {  20,  50 }
};
int quad4_nv = sizeof(quad4) / sizeof(Vertex);
Color quad4c = { 0.00f, 0.60f, 0.80f, 1.00f };  // 0x0099CC

Vertex quad5[] = {  // two vertices outside w/r/t the top edge
    {  50,  70 }, {  60,  70 }, {  60, 100 }, {  50, 100 }
};
int quad5_nv = sizeof(quad5) / sizeof(Vertex);
Color quad5c = { 0.00f, 0.75f, 1.00f, 1.00f };  // 0x00BFFF

Vertex quad6[] = {  // two vertices outside w/r/t the bottom edge
    {  40,  40 }, {  60,  40 }, {  60,  20 }, {  40,  20 }
};
int quad6_nv = sizeof(quad6) / sizeof(Vertex);
Color quad6c = { 0.40f, 0.85f, 1.00f, 1.00f };  // 0x66D9FF

Vertex pent1[] = {
    {  90,  20 }, { 100,  10 }, { 120,  20 }, { 110,  50 }, {  90,  40 }
};
int pent1_nv = sizeof(pent1) / sizeof(Vertex);
Color pent1c = { 0.72f, 0.44f, 0.86f, 1.00f };  // 0xB86FDC

Vertex pent2[] = {
    { 120,  40 }, { 160,  60 }, { 180,  50 }, { 170,  80 }, { 125,  65 }
};
int pent2_nv = sizeof(pent2) / sizeof(Vertex);
Color pent2c = { 0.84f, 0.68f, 0.92f, 1.00f };  // 0xD6ADEB

Vertex hept1[] = {
    { 120,  80 }, { 140,  80 }, { 160,  90 }, { 160, 110 },
    { 140, 120 }, { 120, 110 }, { 110, 100 }
};
int hept1_nv = sizeof(hept1) / sizeof(Vertex);
Color hept1c = { 0.70f, 0.70f, 0.70f, 1.00f };  // 0xB3B3B3

Vertex nona1[] = {
    { 190,  56 }, { 230,  68 }, { 247,  56 }, { 269,  71 }, { 284, 104 },
    { 251, 122 }, { 233, 110 }, { 212, 119 }, { 203,  95 }
};
int nona1_nv = sizeof(nona1) / sizeof(Vertex);
Color nona1c = { 0.87f, 0.72f, 0.53f, 1.00f };  // 0xDEB887

Vertex deca1[] = {
    { 177, 156 }, { 222, 188 }, { 267, 156 }, { 250, 207 }, { 294, 240 },
    { 240, 240 }, { 222, 294 }, { 204, 240 }, { 150, 240 }, { 194, 207 }
};
int deca1_nv = sizeof(deca1) / sizeof(Vertex);
Color deca1c = { 1.00f, 0.65f, 0.00f, 1.00f };  // 0xFFA500

// triangles, clipping region 7
// shades of green

Vertex tri1[] = {
    {  60, 180 }, {  70, 210 }, {  50, 210 }
};
int tri1_nv = sizeof(tri1) / sizeof(Vertex);
Color tri1c = { 0.00f, 0.60f, 0.00f, 1.00f };  // 0x009900

Vertex tri2[] = {
    {  80, 220 }, { 110, 230 }, {  80, 240 }
};
int tri2_nv = sizeof(tri2) / sizeof(Vertex);
Color tri2c = { 0.00f, 0.80f, 0.00f, 1.00f };  // 0x00CC00

Vertex tri3[] = {
    {  50, 250 }, {  70, 250 }, {  60, 280 }
};
int tri3_nv = sizeof(tri3) / sizeof(Vertex);
Color tri3c = { 0.00f, 1.00f, 0.00f, 1.00f };  // 0x00FF00

Vertex tri4[] = {
    {  10, 230 }, {  40, 220 }, {  40, 240 }
};
int tri4_nv = sizeof(tri4) / sizeof(Vertex);
Color tri4c = { 0.40f, 1.00f, 0.40f, 1.00f };  // 0x66FF66

// count of vertices in each clipped polygon
#define	MAX_POLYS	20
int nv[MAX_POLYS];

///
// Drawing-related variables
///

// dimensions of the drawing window
int w_width  = 300;
int w_height = 300;

// our Canvas
Canvas *canvas;

// variables related to drawing the clipping regions
BufferSet clipBuffers;

// variables related to drawing the original polygons
BufferSet polyOutlineBuffers;

// variables related to drawing the resulting polygons
BufferSet clippedPolyBuffers;

// shader program handle
GLuint program;

// names of our GLSL shader files (we assume GLSL 1.30)
const char *vshader = "v130.vert";
const char *fshader = "v130.frag";

///
// Support for individual tests
///

unsigned int which = 0;

#define N_TESTS    15
#define TEST_ALL   0xffffffff
#define IFTEST(n)  if( which & (1 << ((n)-1)) )

///
// iterate through argv converting numeric parameters
// and setting test bits accordingly
//
// invoke as:   set_tests( argc, (const char **) argv );
// check as:    IFTEST(n) { .... }
///
void set_tests( const int argc, const char *argv[] ) {
    char *endptr;

    for( int i = 1; i < argc; ++i ) {
        long int n = strtol( argv[i], &endptr, 10 );
        if( endptr == argv[i] || *endptr != '\0' ) { // no/bad conversion
	    fprintf( stderr, "bad test # '%s' ignored\n", argv[i] );
	} else {
	    if( n >= 1 && n <= N_TESTS ) {
	        which |= (1 << (n-1));
	    } else {
	        fprintf( stderr, "bad test # '%s' ignored\n", argv[i] );
	    }
	}
    }

    if( which == 0 ) {
        which = TEST_ALL;
    }

}

///
// Support function that draws clip regions as line loops
///
void drawClipRegion( Vertex ll, Vertex ur, Canvas &C ) {
    C.setPixel( ll.x, ll.y );  // LL
    C.setPixel( ur.x, ll.y );  // LR
    C.setPixel( ur.x, ur.y );  // UR
    C.setPixel( ll.x, ur.y );  // UL
}

///
// Draw all the clipping rectangles
///
void makeClipOutlines( Canvas &C ) {

    // we draw the clipping regions as white rectangles.
    // all vertices are put into one vertex buffer, and
    // we use glDrawArrays() instead of glDrawElements()
    // to draw them as line loops

    for( int i = 0; i < n_regions; ++i ) {
        drawClipRegion( regions[i][0], regions[i][1], C );
    }
}

///
// Draw a polygon
///
void drawPolygon( Vertex v[], int nv, Canvas &C ) {

    // just put the vertices into the vertex buffer, in order

    for( int i = 0; i < nv; ++i ) {
        C.setPixel( v[i].x, v[i].y );
    }
}

///
// Create the polygon outlines
///
void makePolygonOutlines( Canvas &C ) {

    // here, we draw the original polygons; these
    // will be rendered using line loops

    // region 1
IFTEST( 1 ) {
    C.setColor( quad1c.r, quad1c.g, quad1c.b );
    drawPolygon( quad1, quad1_nv, C );
}
IFTEST( 2 ) {
    C.setColor( quad2c.r, quad2c.g, quad2c.b );
    drawPolygon( quad2, quad2_nv, C );
}

    // region 2
IFTEST( 3 ) {
    C.setColor( quad3c.r, quad3c.g, quad3c.b );
    drawPolygon( quad3, quad3_nv, C );
}
IFTEST( 4 ) {
    C.setColor( quad4c.r, quad4c.g, quad4c.b );
    drawPolygon( quad4, quad4_nv, C );
}
IFTEST( 5 ) {
    C.setColor( quad5c.r, quad5c.g, quad5c.b );
    drawPolygon( quad5, quad5_nv, C );
}
IFTEST( 6 ) {
    C.setColor( quad6c.r, quad6c.g, quad6c.b );
    drawPolygon( quad6, quad6_nv, C );
}

    // region 3
IFTEST( 7 ) {
    C.setColor( pent1c.r, pent1c.g, pent1c.b );
    drawPolygon( pent1, pent1_nv, C );
}
IFTEST( 8 ) {
    C.setColor( pent2c.r, pent2c.g, pent2c.b );
    drawPolygon( pent2, pent2_nv, C );
}

    // region 4
IFTEST( 9 ) {
    C.setColor( hept1c.r, hept1c.g, hept1c.b );
    drawPolygon( hept1, hept1_nv, C );
}

    // region 5
IFTEST( 10 ) {
    C.setColor( nona1c.r, nona1c.g, nona1c.b );
    drawPolygon( nona1, nona1_nv, C );
}

    // region 6
IFTEST( 11 ) {
    C.setColor( deca1c.r, deca1c.g, deca1c.b );
    drawPolygon( deca1, deca1_nv, C );
}

    // region 7
IFTEST( 12 ) {
    C.setColor( tri1c.r, tri1c.g, tri1c.b );
    drawPolygon( tri1, tri1_nv, C );
}
IFTEST( 13 ) {
    C.setColor( tri2c.r, tri2c.g, tri2c.b );
    drawPolygon( tri2, tri2_nv, C );
}
IFTEST( 14 ) {
    C.setColor( tri3c.r, tri3c.g, tri3c.b );
    drawPolygon( tri3, tri3_nv, C );
}
IFTEST( 15 ) {
    C.setColor( tri4c.r, tri4c.g, tri4c.b );
    drawPolygon( tri4, tri4_nv, C );
}
}

///
// Create the filled polygons
///
void makePolygons( Canvas &C ) {
    // temporary vertex array
    Vertex tmp[50];

    ///
    // region one:  quads, shades of red
    ///

IFTEST( 1 ) {
    // entirely inside
    C.setColor( quad1c.r, quad1c.g, quad1c.b );
    nv[0] = clipPolygon( quad1_nv, quad1, tmp, regions[0][0], regions[0][1] );
    if( nv[0] > 0 ) {
        drawPolygon( tmp, nv[0], C );
    }
}

IFTEST( 2 ) {
    // entirely outside
    C.setColor( quad2c.r, quad2c.g, quad2c.b );
    nv[1] = clipPolygon( quad2_nv, quad2, tmp, regions[0][0], regions[0][1] );
    // shouldn't draw anything!
    if( nv[1] > 0 ) {
        drawPolygon( tmp, nv[1], C );
    }
}

    ///
    // region two:  more quads, shades of blue
    ///

IFTEST( 3 ) {
    // two vertices outside w/r/t the right edge
    C.setColor( quad3c.r, quad3c.g, quad3c.b );
    nv[2] = clipPolygon( quad3_nv, quad3, tmp, regions[1][0], regions[1][1] );
    if( nv[2] > 0 ) {
        drawPolygon( tmp, nv[2], C );
    }
}

IFTEST( 4 ) {
    // two vertices outside w/r/t the left edge
    C.setColor( quad4c.r, quad4c.g, quad4c.b );
    nv[3] = clipPolygon( quad4_nv, quad4, tmp, regions[1][0], regions[1][1] );
    if( nv[3] > 0 ) {
        drawPolygon( tmp, nv[3], C );
    }
}

IFTEST( 5 ) {
    // two vertices outside w/r/t the top edge
    C.setColor( quad5c.r, quad5c.g, quad5c.b );
    nv[4] = clipPolygon( quad5_nv, quad5, tmp, regions[1][0], regions[1][1] );
    if( nv[4] > 0 ) {
        drawPolygon( tmp, nv[4], C );
    }
}

IFTEST( 6 ) {
    // two vertices outside w/r/t the bottom edge
    C.setColor( quad6c.r, quad6c.g, quad6c.b );
    nv[5] = clipPolygon( quad6_nv, quad6, tmp, regions[1][0], regions[1][1] );
    if( nv[5] > 0 ) {
        drawPolygon( tmp, nv[5], C );
    }
}

    ///
    // region three: pentagons, outside w/r/t two edges
    ///

IFTEST( 7 ) {
    // outside w/r/t the left and bottom edges
    C.setColor( pent1c.r, pent1c.g, pent1c.b );
    nv[6] = clipPolygon( pent1_nv, pent1, tmp, regions[2][0], regions[2][1] );
    if( nv[6] > 0 ) {
        drawPolygon( tmp, nv[6], C );
    }
}

IFTEST( 8 ) {
    // outside w/r/t the top and right edges
    C.setColor( pent2c.r, pent2c.g, pent2c.b );
    nv[7] = clipPolygon( pent2_nv, pent2, tmp, regions[2][0], regions[2][1] );
    if( nv[7] > 0 ) {
        drawPolygon( tmp, nv[7], C );
    }
}

    ///
    // region four:  outside on top, right, and bottom
    ///

IFTEST( 9 ) {
    C.setColor( hept1c.r, hept1c.g, hept1c.b );
    nv[8] = clipPolygon( hept1_nv, hept1, tmp, regions[3][0], regions[3][1] );
    if( nv[8] > 0 ) {
        drawPolygon( tmp, nv[8], C );
    }
}

    ///
    // region five:  surrounds the clip region
    ///

IFTEST( 10 ) {
    C.setColor( nona1c.r, nona1c.g, nona1c.b );
    nv[9] = clipPolygon( nona1_nv, nona1, tmp, regions[5][0], regions[5][1] );
    if( nv[9] > 0 ) {
        drawPolygon( tmp, nv[9], C );
    }
}

    ///
    // region six:  outside on all four edges
    ///

IFTEST( 11 ) {
    C.setColor( deca1c.r, deca1c.g, deca1c.b );
    nv[10] = clipPolygon( deca1_nv, deca1, tmp, regions[4][0], regions[4][1] );
    if( nv[10] > 0 ) {
        drawPolygon( tmp, nv[10], C );
    }
}

    ///
    // region seven: outside w/r/t one edge
    ///

IFTEST( 12 ) {
    C.setColor( tri1c.r, tri1c.g, tri1c.b );
    nv[11] = clipPolygon( tri1_nv, tri1, tmp, regions[6][0], regions[6][1] );
    if( nv[11] > 0 ) {
        drawPolygon( tmp, nv[11], C );
    }
}

IFTEST( 13 ) {
    C.setColor( tri2c.r, tri2c.g, tri2c.b );
    nv[12] = clipPolygon( tri2_nv, tri2, tmp, regions[6][0], regions[6][1] );
    if( nv[12] > 0 ) {
        drawPolygon( tmp, nv[12], C );
    }
}

IFTEST( 14 ) {
    C.setColor( tri3c.r, tri3c.g, tri3c.b );
    nv[13] = clipPolygon( tri3_nv, tri3, tmp, regions[6][0], regions[6][1] );
    if( nv[13] > 0 ) {
        drawPolygon( tmp, nv[13], C );
    }
}

IFTEST( 15 ) {
    C.setColor( tri4c.r, tri4c.g, tri4c.b );
    nv[14] = clipPolygon( tri4_nv, tri4, tmp, regions[6][0], regions[6][1] );
    if( nv[14] > 0 ) {
        drawPolygon( tmp, nv[14], C );
    }
}
}

///
// Create all our objects
///
void createImage( void )
{
    // start with a clean canvas
    canvas->clear();

    // first, create the clipping region buffers
    //
    // start by putting all the vertices for all
    // the regions into a single set of buffers

    // draw all of them in white
    canvas->setColor( 1.0f, 1.0f, 1.0f );
    makeClipOutlines( *canvas );

    // collect the vertex, element, and color data for these
    clipBuffers.createBuffers( *canvas );

    // next, do the polygon outlines
    canvas->clear();
    makePolygonOutlines( *canvas );
    polyOutlineBuffers.createBuffers( *canvas );

    // finally, do the polygons
    canvas->clear();
    makePolygons( *canvas );
    clippedPolyBuffers.createBuffers( *canvas );

}

///
// OpenGL initialization
///
void init( void )
{
    // Create our Canvas "object"
    canvas = new Canvas( w_width, w_height );

    if( canvas == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
        glfwTerminate();
        exit( 1 );
    }

    // Load shaders and use the resulting shader program
    ShaderError error;
    program = shaderSetup( vshader, fshader, &error );
    if( !program ) {
        cerr << "Error setting up shaders - " << errorString(error) << endl;
	glfwTerminate();
	exit( 1 );
    }

    // OpenGL state initialization
    glEnable( GL_DEPTH_TEST );
    // glEnable( GL_CULL_FACE );
    // glCullFace( GL_BACK );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0f );

    // create the geometry for our shapes.
    createImage();
}

///
// Display the current image
///
void display( void )
{
    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // ensure we have selected the correct shader program
    glUseProgram( program );

    // set up our scale factors for normalization
    GLint sf = glGetUniformLocation( program, "sf" );
    glUniform2f( sf, 2.0f / (w_width - 1.0f), 2.0f / (w_height - 1.0f) );

    ///
    // first, draw the polygon outlines
    ///

    // bind our buffers
    polyOutlineBuffers.selectBuffers( program, "vPosition", "vColor",
        NULL, NULL );

    // draw our shapes
    int skip = 0;
    IFTEST( 1){glDrawArrays( GL_LINE_LOOP, skip, quad1_nv ); skip += quad1_nv;}
    IFTEST( 2){glDrawArrays( GL_LINE_LOOP, skip, quad2_nv ); skip += quad2_nv;}
    IFTEST( 3){glDrawArrays( GL_LINE_LOOP, skip, quad3_nv ); skip += quad3_nv;}
    IFTEST( 4){glDrawArrays( GL_LINE_LOOP, skip, quad4_nv ); skip += quad4_nv;}
    IFTEST( 5){glDrawArrays( GL_LINE_LOOP, skip, quad5_nv ); skip += quad5_nv;}
    IFTEST( 6){glDrawArrays( GL_LINE_LOOP, skip, quad6_nv ); skip += quad6_nv;}
    IFTEST( 7){glDrawArrays( GL_LINE_LOOP, skip, pent1_nv ); skip += pent1_nv;}
    IFTEST( 8){glDrawArrays( GL_LINE_LOOP, skip, pent2_nv ); skip += pent2_nv;}
    IFTEST( 9){glDrawArrays( GL_LINE_LOOP, skip, hept1_nv ); skip += hept1_nv;}
    IFTEST(10){glDrawArrays( GL_LINE_LOOP, skip, nona1_nv ); skip += nona1_nv;}
    IFTEST(11){glDrawArrays( GL_LINE_LOOP, skip, deca1_nv ); skip += deca1_nv;}
    IFTEST(12){glDrawArrays( GL_LINE_LOOP, skip, tri1_nv  ); skip += tri1_nv;}
    IFTEST(13){glDrawArrays( GL_LINE_LOOP, skip, tri2_nv  ); skip += tri2_nv;}
    IFTEST(14){glDrawArrays( GL_LINE_LOOP, skip, tri3_nv  ); skip += tri3_nv;}
    IFTEST(15){glDrawArrays( GL_LINE_LOOP, skip, tri4_nv  ); skip += tri4_nv;}

    ///
    // next, draw the clipped polygons
    ///

    // bind our buffers
    clippedPolyBuffers.selectBuffers( program, "vPosition", "vColor",
        NULL, NULL );

    // draw our shapes
    //
    // be sure to only draw what's there
    skip = 0;
    for( int i = 0; i < MAX_POLYS; ++i ) {
        if( nv[i] ) {
            glDrawArrays( GL_TRIANGLE_FAN, skip, nv[i] ); skip += nv[i];
        }
    }

    ///
    // finally, draw the clip region outlines (we do these
    // last so that they show up on top of everything else)
    ///

    // bind our buffers
    clipBuffers.selectBuffers( program, "vPosition", "vColor",
        NULL, NULL );

    // draw our shapes
    glDrawArrays( GL_LINE_LOOP,  0, 4 );
    glDrawArrays( GL_LINE_LOOP,  4, 4 );
    glDrawArrays( GL_LINE_LOOP,  8, 4 );
    glDrawArrays( GL_LINE_LOOP, 12, 4 );
    glDrawArrays( GL_LINE_LOOP, 16, 4 );
    glDrawArrays( GL_LINE_LOOP, 20, 4 );
    glDrawArrays( GL_LINE_LOOP, 24, 4 );
}

///
// Event callback routines
///

///
// Handle keyboard input
///
void keyboard( GLFWwindow *window, int key, int scan, int action, int modes )
{
    switch( key ) {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose( window, 1 );
            break;
    }
}

///
// Error callback for GLFW
///
void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}

///
// Main program for polygon clip assignment
///
int main( int argc, char *argv[] )
{
    glfwSetErrorCallback( glfwError );

    set_tests( argc, (const char **) argv );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 3 - Polygon Clipping", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: " << glewGetErrorString(err) << endl;
        glfwTerminate();
        exit( 1 );
    }

    if( ! GLEW_VERSION_3_0 ) {
        cerr << "GLEW: OpenGL 3.0 not available" << endl;
        if( !GLEW_VERSION_2_1 ) {
	    cerr << "GLEW: OpenGL 2.1 not available, either!" << endl;
            glfwTerminate();
            exit( 1 );
        }
    }
#endif

    // determine whether or not we can use GLSL 1.30
    int maj = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MAJOR );
    int min = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MINOR );

    cerr << "GLFW: using " << maj << "." << min << " context" << endl;
    if( maj < 3 ) {
        // nope!
	cerr << "Using alternate shaders." << endl;
        vshader = "v120.vert";
	fshader = "v120.frag";
    }

    init();

    glfwSetKeyCallback( window, keyboard );

    while( !glfwWindowShouldClose(window) ) {
        display();
        glfwSwapBuffers( window );
        glfwWaitEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
