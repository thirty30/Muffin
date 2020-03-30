#version 420

uniform mat4 MVP;

uniform mat4 matModel;	//Model or World
uniform mat4 matView;	//View or camera
uniform mat4 matProj;	//Projection transform
uniform mat4 matModelInverseTranspose;

const int MAXNUMBEROFBONES = 100;
uniform mat4 matBonesArray[MAXNUMBEROFBONES];
uniform bool isSkinnedMesh;

//in variables
in vec4 vColor;
in vec4 vPosition;
in vec4 vNormal;
in vec4 vUVx2;
in vec4 vTangent;
in vec4 vBiNormal;
in vec4 vBoneID;
in vec4 vBoneWeight;



//out variables
out vec4 in_fColour;
out vec4 in_fVertWorldLocation;    //location of the vertex in the world
flat out vec4 in_fNormal;
out vec4 in_fUVx2;

void main()
{
	if ( isSkinnedMesh == false )
	{
		mat4 matMVP = matProj * matView * matModel;
	    gl_Position = matMVP * vPosition;
	    in_fColour = vColor;
	    in_fVertWorldLocation = matModel * vPosition;
	    in_fNormal = matModelInverseTranspose* vNormal;
	    in_fUVx2 = vUVx2;
	}
	else
	{
		mat4 BoneTransform = matBonesArray[ int(vBoneID[0]) ] * vBoneWeight[0];
		BoneTransform += matBonesArray[ int(vBoneID[1]) ] * vBoneWeight[1];
		BoneTransform += matBonesArray[ int(vBoneID[2]) ] * vBoneWeight[2];
		BoneTransform += matBonesArray[ int(vBoneID[3]) ] * vBoneWeight[3];

		vec4 vertBone = BoneTransform * vPosition;
		mat4 matMVP = matProj * matView * matModel;
		gl_Position = matMVP * vertBone;
	    in_fVertWorldLocation = matModel * vertBone;
	    mat4 matModelAndBone = matModel * BoneTransform;
	    in_fNormal = inverse(transpose(matModelAndBone)) * vNormal;

	    in_fColour = vColor;
	    in_fUVx2 = vUVx2;
	}
}