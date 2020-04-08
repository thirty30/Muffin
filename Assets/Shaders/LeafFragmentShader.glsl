#version 420

//in variables
in vec4 in_fColour;	
in vec4 in_fVertWorldLocation;
in vec4 in_fNormal;
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
	vec4 color = texture( DiffuseMap, in_fUVx2.st );

	float bo = 0.09;
	vec2 uvs = in_fUVx2.st;

	vec3 texRGB1 = texture( DiffuseMap, uvs.st ).rgb;
	vec3 texRGB2 = texture( DiffuseMap, vec2( uvs.s + bo, uvs.t) ).rgb;
	vec3 texRGB3 = texture( DiffuseMap, vec2( uvs.s + bo, uvs.t - bo) ).rgb;
	vec3 texRGB4 = texture( DiffuseMap, vec2( uvs.s + bo, uvs.t + bo) ).rgb;
	vec3 texRGB5 = texture( DiffuseMap, vec2( uvs.s - bo, uvs.t) ).rgb;
	vec3 texRGB6 = texture( DiffuseMap, vec2( uvs.s - bo, uvs.t - bo) ).rgb;
	vec3 texRGB7 = texture( DiffuseMap, vec2( uvs.s - bo, uvs.t + bo) ).rgb;
	vec3 texRGB8 = texture( DiffuseMap, vec2( uvs.s, uvs.t + bo) ).rgb;
	vec3 texRGB9 = texture( DiffuseMap, vec2( uvs.s, uvs.t - bo) ).rgb;
	vec3 resRGB = (texRGB1 + texRGB2 + texRGB3 + texRGB4 + texRGB5 + texRGB6 + texRGB7 + texRGB8 + texRGB9) / 9.0;
	
	if(resRGB.r >= 0.1 && resRGB.g > 0.78 && resRGB.b > 0.1)
	{
		discard;
	}
	resRGB *= 2.0f;
	out_pixelColour.rgb = resRGB;
}
