#version 420

uniform mat4 MVP;

uniform mat4 matModel;	//Model or World
uniform mat4 matView;	//View or camera
uniform mat4 matProj;	//Projection transform

in vec3 vColor;
in vec3 vPosition;

out vec3 color;
out vec4 vertWorld;		//location of the vertex in the world

void main()
{
	mat4 matMVP = matProj * matView * matModel;
    gl_Position = matMVP * vec4(vPosition, 1.0);
    color = vColor;
    vertWorld = matModel * vec4(vPosition, 1.0);
}