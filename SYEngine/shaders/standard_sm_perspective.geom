#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

// light matrices are projection * view for each of 6 light directions
uniform mat4 lightMatrices[6];

out vec4 fragPos;

void main() 
{
	for (int face = 0; face < 6; ++face) 
	{
		// Which face of "cube" we are writing to
		gl_Layer = face;
		for (int i = 0; i < 3; ++i) 
		{
			fragPos = gl_in[i].gl_Position;
			gl_Position = lightMatrices[face] * fragPos; 
			// This writes at gl_position vertex in selected face
			EmitVertex();
		}
		// Finished drawing triangle
		EndPrimitive();
	}
}
// After this we got 6 triangles view from light source computed, each for one light direction... final 
// fragment colour will be computed from those base od position 

