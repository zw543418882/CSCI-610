///
//  Buffers.h
//
//  Vertex and element buffer management
//
//  Author:  Warren R. Carithers
//  Date:    2017/02/11
//  Updated: 2019/02/26
//
//  This file should not be modified by students.
///

#ifndef _BUFFERS_H_
#define _BUFFERS_H_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

using namespace std;

#include "Pipeline.h"

///
// How to calculate an offset into the vertex buffer
///
#define BUFFER_OFFSET(i)        ((GLvoid *)(((char *)0) + (i)))

///
// All the relevant information needed to keep
// track of vertex and element buffers
///

class BufferSet {

public:
    // buffer handles
    GLuint vbuffer, ebuffer;

    // total number of vertices
    int numElements;

    // component sizes (bytes)
    long vSize, eSize, tSize, cSize, nSize;

    // have these already been set up?
    bool bufferInit;

public:

    ///
    // Constructor
    ///
    BufferSet( void );

    ///
    // initBuffer(buf) - reset the supplied buffer to its "empty" state
    ///
    void initBuffer( void );

    ///
    // dumpBuffer(buf) - dump the contents of the BufferSet
    //
    // @param which - description of the buffer
    ///
    void dumpBuffer( const char *which );

    ///
    // makeBuffer(target,data,size) - make a vertex or element array buffer
    //
    // @param target - which type of buffer to create
    // @param data   - source of data for buffer (or NULL)
    // @param size   - desired length of buffer
    //
    // @return the ID of the new buffer
    ///
    GLuint makeBuffer( GLenum target, const void *data, GLsizei size );

    ///
    // createBuffers(buf,pipeline) - create a set of buffers for the object
    //     currently held in 'pipeline's Canvas.
    //
    // @param P   - the Pipeline we'll use for drawing
    //              (must use a pointer to get polymorphism because it's C++!)
    ///
    void createBuffers( Pipeline *P );

    ///
    // selectBuffers() - bind the correct vertex and element buffers
    //
    // @param program - GLSL program object
    // @param vp      - name of the position attribute variable
    // @param vc      - name of the color attribute variable (or NULL)
    // @param vn      - name of the normal attribute variable (or NULL)
    // @param vt      - name of the texture coord attribute variable (or NULL)
    ///
    void selectBuffers( GLuint program,
        const char *vp, const char * vc, const char *vn, const char *vt );

};

#endif
