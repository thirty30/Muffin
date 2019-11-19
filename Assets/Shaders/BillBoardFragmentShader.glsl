#version 420

//in variables
in vec4 in_fColour;	
in vec4 in_fNormal;
in vec4 in_fVertWorldLocation;
in vec4 in_fUVx2;

//out variables
out vec4 out_pixelColour;

//block
const int LIGHT_TYPE_DIRECTIONAL = 1;
const int LIGHT_TYPE_POINT = 2;
const int LIGHT_TYPE_SPOT = 3;

struct sLight
{
	int nLightType;		// 0:directional light 1:pointlight 2:spot light
	int bEnable;
	vec4 vPosition;
	vec4 vDiffuse;	
	vec4 vSpecular;		// rgb
	float fSpecularPower;
	vec4 vAttenuation;	// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 vDirection;	// Spot, directional lights
	vec4 vParm1;		// x = inner angle, y = outer angle, z = TBD
	vec4 vParm2;
};

//uniform variables
uniform vec4 un_vDiffuseColour;
uniform vec4 un_vSpecularColour;
uniform vec4 un_vEyeLocation;
uniform int un_nLightNum;
uniform sLight un_LightArray[80];
uniform int un_samplerCount;
uniform sampler2D[16] un_Samplers;

void main()  
{
	vec3 vVertexMaterialColour = un_vDiffuseColour.rgb;
	if (un_samplerCount > 0)
	{
		vec3 color = texture( un_Samplers[0], in_fUVx2.st ).rgb;
		float grey = (color.r + color.g + color.b) / 3.0f;
		if (color.r < 0.1f)
		{	
			
			//discard;
		}
		out_pixelColour.a = grey;
		vVertexMaterialColour = color;
	}
	out_pixelColour.rgb = vVertexMaterialColour.rgb;
}
