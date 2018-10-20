#version 330

layout (location = 0) in vec3 pos;

layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

const int MAX_BONES = 100;

uniform int bIsSkeletonAnimated;
uniform mat4 model;
uniform mat4 gBones[MAX_BONES];

void main() 
{

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

	gl_Position = model * boneTransform * vec4(pos, 1.0f);
}