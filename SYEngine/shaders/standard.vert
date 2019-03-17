#version 330                                
                               
/////////////////////////////////////
// Input from VBOs
/////////////////////////////////////

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 textureUVs;             
layout (location = 2) in vec3 vertexNormal;


/////////////////////////////////////
// Uniforms
/////////////////////////////////////

uniform mat4 u_modelToWorldTransfromMatrix;
uniform mat4 u_MVPTransformMatrixPerspective;
uniform mat4 u_MVPTransformMatrixDirLights;

/////////////////////////////////////
// Output to shaders
/////////////////////////////////////

out vec2 _textureCoords;
out vec3 _vertexNormal;
out vec3 _fragmentPosWorldSpace;
out vec4 _vertexPositionInDirectionalLightSpace;


void main()                                
{         
	// Set final texture coordinates send from engine.
	_textureCoords = textureUVs;

	//! Get vertex position in directional light space
    _vertexPositionInDirectionalLightSpace = u_MVPTransformMatrixDirLights * vec4(vertexPosition, 1.0);
	
	//! Correct normal
	_vertexNormal = mat3(transpose(inverse(u_modelToWorldTransfromMatrix))) * vertexNormal;
	
	//! Fragment position in World Space
	_fragmentPosWorldSpace = (u_modelToWorldTransfromMatrix * vec4(vertexPosition, 1.0)).xyz; 

	//! Calculate vertexp position
    gl_Position = u_MVPTransformMatrixPerspective * vec4(vertexPosition, 1.0f);
}                            