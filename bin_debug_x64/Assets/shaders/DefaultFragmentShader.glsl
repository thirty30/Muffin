#version 420

in vec3 color;
in vec4 vertWorld;

uniform vec3 newColour;
uniform float newColourR;
uniform float newColourG;
uniform float newColourB;

uniform vec3 lightPosition;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
    //gl_FragColor = vec4(newColour, 1.0);
    float dist = distance(lightPosition, vertWorld.xyz);
    float linearAttenuation = 2.0f;
    float attenuation = 1.0f / ( linearAttenuation * dist);
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragColor *= attenuation;
}
