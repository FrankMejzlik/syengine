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
uniform mat4 u_MVPTransformMatrixOrtho;


out float distToCamera;

void main()
{
	// Place this vertex into world relative to light position
	gl_Position = u_MVPTransformMatrixOrtho * vec4(vertexPosition, 1.0f);
}
 