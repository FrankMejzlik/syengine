#version 330                            

////////////////////////////////////////////
// Output layout attributes
////////////////////////////////////////////


layout( location = 0 ) out vec4 fragmentColour;


in float distToCamera;

void main() 
{
    fragmentColour = vec4(distToCamera, distToCamera, distToCamera, 0.0f);
}