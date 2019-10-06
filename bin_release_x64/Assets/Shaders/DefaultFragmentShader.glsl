#version 420

in vec3 color;
in vec4 vertWorld;

uniform vec3 LightColor;
uniform vec3 LightPosition;

void main()
{
    gl_FragColor = vec4(color, 1.0);
    //gl_FragColor = vec4(LightColor, 1.0);
    //float dist = distance(LightPosition, vertWorld.xyz);
    //float linearAttenuation = 0.5f;
    //float attenuation = 1.0f / ( linearAttenuation * dist);
    //gl_FragColor *= attenuation;
}
