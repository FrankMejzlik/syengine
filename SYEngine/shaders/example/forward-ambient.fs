#version 120


vec2 CalcParallaxTexCoords(sampler2D dispMap, mat3 tbnMatrix, vec3 directionToEye, vec2 texCoords, float scale, float bias)
{
	return texCoords.xy + (directionToEye * tbnMatrix).xy * (texture2D(dispMap, texCoords.xy).r * scale + bias);
}

float SampleShadowMap(sampler2D shadowMap, vec2 coords, float compare)
{
	return step(compare, texture2D(shadowMap, coords.xy).r);
}


varying vec2 texCoord0;
varying vec3 worldPos0;
varying mat3 tbnMatrix;

uniform vec3 R_ambient;
uniform vec3 C_eyePos;
uniform sampler2D diffuse;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;

void main()
{
	vec3 directionToEye = normalize(C_eyePos - worldPos0);
	vec2 texCoords = CalcParallaxTexCoords(dispMap, tbnMatrix, directionToEye, texCoord0, dispMapScale, dispMapBias);
	gl_FragColor = texture2D(diffuse, texCoords) * vec4(R_ambient, 1);
}
