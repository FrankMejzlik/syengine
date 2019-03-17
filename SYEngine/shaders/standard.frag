#version 330

/////////////////////////////////////
// Input from shaders
/////////////////////////////////////

in vec2 _textureCoords;
in vec3 _vertexNormal;
in vec3 _fragmentPosWorldSpace;
in vec4 _vertexPositionInDirectionalLightSpace;


/////////////////////////////////////
// Uniforms
/////////////////////////////////////

uniform DirectionalLight u_directionalLights;
uniform sampler2D u_diffuseTexture;
uniform sampler2D u_normalMapTexture;
uniform sampler2D u_directionalShadowMaps;
uniform Material u_material;
uniform vec3 u_eyePosition;


/////////////////////////////////////
// Output to framebuffer
/////////////////////////////////////

layout( location = 0 ) out vec4 fragmentColour;


/////////////////////////////////////
// Structures
/////////////////////////////////////

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct Material
{
	float specularIntensity;
	float shininessIntensity;
};




float CalcDirectionalShadowFactor(DirectionalLight light) 
{
	// Get normalized fragment coordinates in light space
	vec3 fragPositionRelToLight = _vertexPositionInDirectionalLightSpace.xyz / _vertexPositionInDirectionalLightSpace.w;

	// Offset them to [0, 1] space
	fragPositionRelToLight = (fragPositionRelToLight * 0.5) + 0.5;
	
	// Get distance from fragment
	float fragmentDistance = fragPositionRelToLight.z;
	
	// Normalize normal in this fragment
	vec3 nnormal = normalize(_vertexNormal);

	// Normalize light direction
	vec3 lightDir = normalize(u_directionalLight.direction);
	
	// Calculate bias
	float bias = max(0.0005 * (1.0 - dot(nnormal, lightDir)), 0.0005);

	// Initialize shadow factor
	float shadowFactor = 0.0f;

	// Get texel value from shadow map
	float closestFragment = texture(u_directionalShadowMap, fragPositionRelToLight.xy).r;

	// If this fragment further than closes fragment
	if (fragmentDistance > (closestFragment + bias)
	{
		shadowFactor = 0.0f;
	} 
	else
	{
		shadowFactor = 1.0f;
	}
	
	// If away from shadow map
	if(fragPositionRelToLight.z > 1.0)
	{
		shadowFactor = 0.0;
	}									
	
	return shadowFactor;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor)
{
	// Calc ambient colour
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	// Calc diffuse factor
	float diffuseFactor = max(dot(normalize(_vertexNormal), normalize(direction)), 0.0f);

	// Calc diffuse colour
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	// Set specular colour to white
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	// If some diffuse light should be present
	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(u_eyePosition - _fragmentPosWorldSpace);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(_vertexNormal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);

		// If some specular should be present
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, u_material.shininessIntensity);
			specularColour = vec4(light.colour * u_material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return ambientColour + (shadowFactor * (diffuseColour + specularColour));
}

vec4 CalcDirectionalLight()
{
	float shadowFactor = CalcDirectionalShadowFactor(u_directionalLight);

	// Calculate final colour based on directional light
	return CalcLightByDirection(u_directionalLight.base, u_directionalLight.direction, shadowFactor);
}


void main()
{
	// Calculate fragment colour from lights
	vec4 fragmentLightColour = CalcDirectionalLight();
	
	// Get final fragment colour
	fragmentColour = texture(u_diffuseTexture, _textureCoords) * fragmentLightColour;
}