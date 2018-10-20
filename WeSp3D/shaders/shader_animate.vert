#version 330                                

// Data in buffers
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;             
layout (location = 2) in vec3 norm;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in ivec4 Weights;

out vec4 vCol; 
out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

const int MAX_BONES = 100;

uniform mat4 model;                          
uniform mat4 view;        
uniform mat4 projection;   
uniform mat4 directionalLightTransform;
uniform mat4 gBones[MAX_BONES];

void main()                                
{                      
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
    BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform     += gBones[BoneIDs[3]] * Weights[3];


	vec4 PosL    = BoneTransform * vec4(pos, 1.0);
    gl_Position = (projection * view * model) * PosL;

    directionalLightSpacePos = (directionalLightTransform * model) *(BoneTransform * vec4(pos, 1.0));

	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	texCoords = tex;

	vec4 NormalL   = BoneTransform * vec4(norm, 0.0);

	normal = -(transpose(inverse(model)) * NormalL).xyz;	
	fragPos = ((model * PosL)).xyz;  	
}                            