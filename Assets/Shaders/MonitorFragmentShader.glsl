#version 420

//in variables
in vec4 in_fColour;	
in vec4 in_fVertWorldLocation;
flat in vec4 in_fNormal;
in vec4 in_fUVx2;

//out variables
out vec4 out_pixelColour;

uniform sampler2D DiffuseMap;

void main()  
{
	//out_pixelColour = texture( DiffuseMap, in_fUVx2.st );

	float bo = 0.03;
	vec2 uvs = in_fUVx2.st;
	float screenW= 1600;
	float screenH = 900;
	//uvs.s = gl_FragCoord.x / screenW;
	//uvs.t = gl_FragCoord.y / screenH;

	//uvs.s = in_fVertWorldLocation.x / 100.0;
	//uvs.t = in_fVertWorldLocation.y / 100.0;

	vec3 texRGB1 = texture( DiffuseMap, uvs.st ).rgb;
	vec3 texRGB2 = texture( DiffuseMap, vec2( uvs.s + bo, uvs.t) ).rgb;
	vec3 texRGB3 = texture( DiffuseMap, vec2( uvs.s - bo, uvs.t) ).rgb;
	vec3 texRGB4 = texture( DiffuseMap, vec2( uvs.s, uvs.t + bo) ).rgb;
	vec3 texRGB5 = texture( DiffuseMap, vec2( uvs.s, uvs.t - bo) ).rgb;
	vec3 resRGB = (texRGB1 + texRGB2 + texRGB3 + texRGB4 + texRGB5) / 5.0 * 2.0;

	out_pixelColour.rgb = resRGB;
	//out_pixelColour.rgb = vec3(resRGB.r * 0.3, resRGB.g * 0.59, resRGB.b * 0.11);
	out_pixelColour.a = 1.0;
}
