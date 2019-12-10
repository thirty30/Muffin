#version 420

uniform mat4 MVP;

uniform mat4 matModel;	//Model or World
uniform mat4 matView;	//View or camera
uniform mat4 matProj;	//Projection transform
uniform mat4 matModelInverseTranspose;

//in variables
in vec4 vColor;
in vec4 vPosition;
in vec4 vNormal;
in vec4 vUVx2;

//out variables
out vec4 in_fColour;
out vec4 in_fVertWorldLocation;    //location of the vertex in the world
flat out vec4 in_fNormal;
out vec4 in_fUVx2;

void main()
{
	mat4 matMVP = matProj * matView * matModel;
    gl_Position = matMVP * vPosition;
    in_fColour = vColor;
    in_fVertWorldLocation = matModel * vPosition;
    in_fNormal = matModelInverseTranspose* vNormal;
    in_fUVx2 = vUVx2;
}