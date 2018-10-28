#version 330

in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;


void main() 
{
	// Get distance between frambent being rendered and light source
	float distance = length(fragPos.xyz - lightPos);

	// Make it relative to farPlane
	// it assumes that near plane is at nearly 0
	distance = distance/farPlane;

	// Set depth of this frament
	gl_FragDepth = distance;


}