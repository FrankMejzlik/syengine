#version 330

////////////////////////////////////////////
// Layout attributes
////////////////////////////////////////////

//! Vertex position send from application
layout (location = 0) in vec3 pos;


////////////////////////////////////////////
// Uniform variables
////////////////////////////////////////////

//! Model->World transform of vertex relative to light source
uniform mat4 MVPTransformMatrix;

void main()
{
	// Place this vertex into world relative to light position
	gl_Position = MVPTransformMatrix * vec4(pos, 1.0f);
}
