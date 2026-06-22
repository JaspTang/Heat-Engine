/*  Fragment Shader
    Convert the data from vertex shader to colored pixels on the screen
    (Usually happens after rasterization but no rasterization needed yet)
    Runs once per pixel of the incoming vertex point
*/

/* Version 3.3 & core version */
#version 330 core

/*  In/Out
    Take what we get from our vertex shader (vTemp)
    Expect an output a 4-element vector representing color
    Take temperature as input and convert to color as output
*/
in float vTemp;
out vec4 color;

/*  Main
    Calculate color from our Temperature Data
    In (r,g,b) cold is represented by pure blue
                hot is represented by pure red
    color is a new 4-element vector produced by the following math:
    mix(cold, got, vTemp), 1:
    mix (a, b, t) = (1 - t)*a + t*b
    last number is alpha value (opaqueness)
*/
void main() {
    vec3 cold = vec3(0,0,1);
    vec3 hot = vec3(1,0,0);
    color = vec4(mix(cold, hot, vTemp), 1);
}
