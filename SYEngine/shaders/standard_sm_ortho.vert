#version 330

////////////////////////////////////////////
// Input layout attributes
////////////////////////////////////////////

//! Vertex position send from application
layout (location = 0) in vec3 vertexPosition;


////////////////////////////////////////////
// Uniform variables
////////////////////////////////////////////

//! Model->World transform of vertex relative to light source
uniform mat4 u_MVPTransformMatrix;


out float distToCamera;

void main()
{

vec4 pos = u_MVPTransformMatrix * vec4(vertexPosition, 1.0f);

	distToCamera = pos.z / 100.0f;


	// Place this vertex into world relative to light position
	gl_Position = pos;

	
}
 