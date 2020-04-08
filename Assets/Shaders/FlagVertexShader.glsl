#version 420

uniform mat4 MVP;

uniform mat4 matModel;	//Model or World
uniform mat4 matView;	//View or camera
uniform mat4 matProj;	//Projection transform
uniform mat4 matModelInverseTranspose;
uniform float Offset;
uniform sampler2D WindMap;

//in variables
in vec4 vColor;
in vec4 vPosition;
in vec4 vNormal;
in vec4 vUVx2;

//out variables
flat out vec4 in_fColour;
out vec4 in_fVertWorldLocation;    //location of the vertex in the world
out vec4 in_fNormal;
out vec4 in_fUVx2;

void main()
{
	vec4 vPos = vPosition;
	vec4 uv = vUVx2;
	uv.s += Offset * 0.6;
    vec3 Color = texture( WindMap, uv.st ).rgb;
    vPos.z += Color.r * 0.7;

	mat4 matMVP = matProj * matView * matModel;
    gl_Position = matMVP * vPos;
    in_fColour = vColor;
    in_fVertWorldLocation = matModel * vPos;
    in_fNormal = matModelInverseTranspose* vNormal;
    in_fUVx2 = vUVx2;


}