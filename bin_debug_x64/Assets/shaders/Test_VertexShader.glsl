#version 110
uniform mat4 MVP;
attribute vec3 vColor;
attribute vec3 vPositon;
varying vec3 color;
void main()
{
	vec3 tempPos = vPositon;
	tempPos.x *= 1.0f;
	tempPos.y *= 1.0f;
	tempPos.z *= 1.0f;
    gl_Position = MVP * vec4(tempPos, 1.0);
    color = vColor;
}