/*  Vertex Shader
    For a given set of data, transfer it into points
    How will the GPU use our input data
*/

/* Version 3.3 & core GLSL */
#version 330 core

/*  Layout
    Define a new vertex with 
    1. the first attribute being a 2-element vector for positions
    2. the second attribute being a double for temperature
*/

layout(location = 0) in vec2 pos;
layout(location = 1) in double temp;

/* In/Out: Out a double vTemp as defined in main */
out double vTemp;

/*  Main
    take the temperature data and assign it to new data vTemp for our GPU
    Set up the vertex to be 100 pixels big and have it defined by a
    4-element vector with 1 attribute for position, 1 for depth, 1 for homogeneous coordinate
    
    gl_Position - position of vector
    gl_PointSize - size of vector as defined in pixels on screen
*/

void main() {
    vTemp = temp;

    gl_Position = vec4(pos, 0.0, 1.0);
    gl_PointSize = 100.0;

}
