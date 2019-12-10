#version 420

//in variables
in vec4 in_fColour;	
in vec4 in_fVertWorldLocation;
flat in vec4 in_fNormal;
in vec4 in_fUVx2;

//out variables
out vec4 out_pixelColour;

//block
const int LIGHT_TYPE_DIRECTIONAL = 1;
const int LIGHT_TYPE_POINT = 2;
const int LIGHT_TYPE_SPOT = 3;

struct sLight
{
	int nLightType;		// 0:directional light 1:pointlight 2:spot light
	int bEnable;
	vec4 vPosition;
	vec4 vDiffuse;	
	vec4 vSpecular;		// rgb
	float fSpecularPower;
	vec4 vAttenuation;	// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 vDirection;	// Spot, directional lights
	vec4 vParm1;		// x = inner angle, y = outer angle, z = TBD
	vec4 vParm2;
};

//uniform variables
uniform vec4 un_vDiffuseColour;
uniform vec4 un_vSpecularColour;
uniform vec4 un_vEyeLocation;
uniform int un_nLightNum;
uniform sLight un_LightArray[80];
uniform int un_samplerCount;
uniform sampler2D[16] un_Samplers;

void main()  
{
	vec3 vVertexMaterialColour = un_vDiffuseColour.rgb;
	if (un_samplerCount > 0)
	{
		vVertexMaterialColour = texture( un_Samplers[0], in_fUVx2.st ).rgb;
	}
	vec3 vVertexNormal = normalize(in_fNormal.xyz);
	vec3 vVertexWorldPos = in_fVertWorldLocation.xyz;
	vec4 vFinalObjectColour = vec4( 0.0f, 0.0f, 0.0f, 1.0f );

	for (int i = 0; i < un_nLightNum; i++)
	{
		sLight objCurLight = un_LightArray[i];
		if (objCurLight.bEnable == 0)
		{
			continue;
		}

		vec3 vLightDiffuse = vec3(1.0f, 1.0f, 1.0f);
		vec3 vLightSpecular = vec3(0.0f, 0.0f, 0.0f);

		if (objCurLight.nLightType == LIGHT_TYPE_DIRECTIONAL)	// ONLY direction, No position
		{
			float fDotProduct = dot((-objCurLight.vDirection.xyz), vVertexNormal.xyz);
			vLightDiffuse = objCurLight.vDiffuse.rgb * max(0.0f, fDotProduct);
			//vLightDiffuse *= objCurLight.vDiffuse.rgb;
			vFinalObjectColour.rgb += (vVertexMaterialColour.rgb * vLightDiffuse.rgb) + (un_vSpecularColour.rgb  * vLightSpecular.rgb);
		}
		else if (objCurLight.nLightType == LIGHT_TYPE_POINT)
		{
			vec3 vLightToVertex = vVertexWorldPos.xyz - objCurLight.vPosition.xyz;
			float fDistanceToLight = length(vLightToVertex);
			vec3 vLightDirection = normalize(vLightToVertex);
			float fDotProduct = dot(-vLightDirection, vVertexNormal.xyz);	 
			vLightDiffuse = objCurLight.vDiffuse.rgb * max(0.0f, fDotProduct);

			// Specular
			vec3 vReflectVector = reflect(vLightDirection, vVertexNormal);
			vec3 vEyeVector = normalize(un_vEyeLocation.xyz - vVertexWorldPos.xyz);
			float objectSpecularPower = un_vSpecularColour.w; 
			//vLightSpecular = pow(max(0.0f, dot(vEyeVector, vReflectVector)), objectSpecularPower) * objCurLight.vSpecular.rgb;
			vLightSpecular = pow(max(0.0f, dot(vEyeVector, vReflectVector)), objectSpecularPower) * un_vSpecularColour.rgb;

			// Attenuation
			float fAttenuation = 1.0f /  (objCurLight.vAttenuation.x + objCurLight.vAttenuation.y * fDistanceToLight + objCurLight.vAttenuation.z * fDistanceToLight * fDistanceToLight );
			
			// Total light contribution is Diffuse + Specular
			vLightDiffuse *= fAttenuation;
			vLightSpecular *= fAttenuation;

			vFinalObjectColour.rgb += (vVertexMaterialColour.rgb * vLightDiffuse.rgb) + (un_vSpecularColour.rgb * vLightSpecular.rgb);
		}
		else if (objCurLight.nLightType == LIGHT_TYPE_SPOT)
		{
			vec3 vLightToVertex = vVertexWorldPos.xyz - objCurLight.vPosition.xyz;
			float fDistanceToLight = length(vLightToVertex);
			vec3 vLightDirection = normalize(vLightToVertex);
			float fDotProduct = dot(-vLightDirection, vVertexNormal.xyz);	 
			vLightDiffuse = objCurLight.vDiffuse.rgb * max(0.0f, fDotProduct);

			// Specular
			vec3 vReflectVector = reflect(vLightDirection, vVertexNormal);
			vec3 vEyeVector = normalize(un_vEyeLocation.xyz - vVertexWorldPos.xyz);
			float objectSpecularPower = un_vSpecularColour.w; 
			//vLightSpecular = pow(max(0.0f, dot(vEyeVector, vReflectVector)), objectSpecularPower) * objCurLight.vSpecular.rgb;
			vLightSpecular = pow(max(0.0f, dot(vEyeVector, vReflectVector)), objectSpecularPower) * un_vSpecularColour.rgb;

			// Attenuation
			float fAttenuation = 1.0f /  (objCurLight.vAttenuation.x + objCurLight.vAttenuation.y * fDistanceToLight + objCurLight.vAttenuation.z * fDistanceToLight * fDistanceToLight );
			
			// Total light contribution is Diffuse + Specular
			vLightDiffuse *= fAttenuation;
			vLightSpecular *= fAttenuation;

			vec3 vVertexToLight = normalize(vVertexWorldPos.xyz - objCurLight.vPosition.xyz);
			float fLightRayAngle = dot( vVertexToLight.xyz, objCurLight.vDirection.xyz );	
			fLightRayAngle = max(0.0f, fLightRayAngle);
			float fInnerConeAngleCos = cos(radians(objCurLight.vParm1.x));
			float fOuterConeAngleCos = cos(radians(objCurLight.vParm1.y));

			// Is it completely outside of the spot?
			if (fLightRayAngle < fOuterConeAngleCos)
			{
				// Dark
				vLightDiffuse = vec3(0.0f, 0.0f, 0.0f);
				vLightSpecular = vec3(0.0f, 0.0f, 0.0f);
			}
			else if ( fLightRayAngle < fInnerConeAngleCos )
			{
				// Angle is between the inner and outer cone
				// (this is called the penumbra of the spot light, by the way)
				// 
				// This blends the brightness from full brightness, near the inner cone
				//	to black, near the outter cone

				float fPenumbraRatio = (fLightRayAngle - fOuterConeAngleCos) / (fInnerConeAngleCos - fOuterConeAngleCos);				  
				vLightDiffuse *= fPenumbraRatio;
				vLightSpecular *= fPenumbraRatio;
			}
			vFinalObjectColour.rgb += (vVertexMaterialColour.rgb * vLightDiffuse.rgb) + (un_vSpecularColour.rgb * vLightSpecular.rgb);
		}
	}
	out_pixelColour = vFinalObjectColour;
}
