#version 420

//in variables
in vec4 in_fColour;	
in vec4 in_fVertWorldLocation;
flat in vec4 in_fNormal;
in vec4 in_fUVx2;

//out variables
out vec4 out_pixelColour;

//uniform variables
uniform vec4 un_vDiffuseColour;
uniform vec4 un_vSpecularColour;
uniform vec4 un_vEyeLocation;
uniform sampler2D DiffuseMap;

void main()  
{
	out_pixelColour = texture( DiffuseMap, in_fUVx2.st );
}
