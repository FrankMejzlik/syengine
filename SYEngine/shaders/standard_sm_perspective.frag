#version 400                             

////////////////////////////////////////////
// Output layout attributes
////////////////////////////////////////////

layout( location = 0 ) out vec4 fragmentColour;


void main() 
{
    fragmentColour = vec4(gl_FragDepth, gl_FragDepth, gl_FragDepth, 1.0f);
}