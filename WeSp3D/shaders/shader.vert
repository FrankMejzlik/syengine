#version 330                                
                                          
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;             
layout (location = 2) in vec3 norm;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in ivec4 Weights;

out vec2 textureCoords;
out vec3 normal;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

const int MAX_BONES = 100;


uniform int bIsSkeletonAnimated;
uniform mat4 model;                          
uniform mat4 view;        
uniform mat4 projection;   
uniform mat4 directionalLightTransform;
uniform mat4 gBones[MAX_BONES];

void main()                                
{         
	// Set final texture coordinates send from engine.
	textureCoords = tex;

	// Compose transforms from all 4 bones.
	// TODO: Make weight count dynamic.
	mat4 boneTransform = mat4(1.0);

	// If this is skeleton animated vertex.
	if (bIsSkeletonAnimated != 0) {
		boneTransform = gBones[BoneIDs[0]] * Weights[0];
		boneTransform     += gBones[BoneIDs[1]] * Weights[1];
		boneTransform     += gBones[BoneIDs[2]] * Weights[2];
		boneTransform     += gBones[BoneIDs[3]] * Weights[3];
	}

	// Get final screen position of this vertex.
	/*
		Take model space coordinates -> Model to World -> World to View -> View to Screen.
	*/
    gl_Position = (projection * view * model) * (boneTransform * vec4(pos, 1.0));

	// Get vertex position in directional light space
    directionalLightSpacePos = directionalLightTransform * model * boneTransform * vec4(pos, 1.0);
	
	// Set normal vector for this vertex.
	normal = mat3(transpose(inverse(model))) *  vec3(boneTransform * vec4(norm, 0.0f));
	
	// Final fragment position.
	fragPos = (model * (boneTransform * vec4(pos, 1.0))).xyz; 
}                            