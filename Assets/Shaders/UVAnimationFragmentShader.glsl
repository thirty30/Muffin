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
uniform float AutoFloatOffset;
uniform int FramePerSecond;
uniform int AcrossNum;
uniform int DownNum;

void main()  
{
	float frametime = 1.0 / FramePerSecond;
	int idx = int(AutoFloatOffset / frametime) % (AcrossNum * DownNum);
	int row = idx / AcrossNum;
	int col = idx % AcrossNum;

	float u = in_fUVx2.s / 4 + (1.0 / AcrossNum) * col;
	float v = in_fUVx2.t / 4 + (1.0 / DownNum) * (DownNum - 1 - row);
	vec4 Color = texture( DiffuseMap, vec2(u, v) );
	if (Color.r < 0.3 && Color.g < 0.3 && Color.b < 0.3)
	{
		discard;
	}

	out_pixelColour = Color;
}
