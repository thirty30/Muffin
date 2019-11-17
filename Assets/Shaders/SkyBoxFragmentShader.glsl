#version 420

//in variables
in vec4 in_fColour;
in vec4 in_fNormal;
in vec4 in_fVertWorldLocation;
in vec4 in_fUVx2;

//out variables
out vec4 out_pixelColour;
uniform samplerCube un_Sampler;

void main()  
{
	vec3 skyColour = texture( un_Sampler, -in_fNormal.xyz ).rgb;
	out_pixelColour.rgb = skyColour.rgb;
	out_pixelColour.a = 1.0f;
}
