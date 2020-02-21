#pragma once
#include "TMuffinSysInclude.h"

T_INLINE vector<glm::vec3> GenerateBezierCurve(glm::vec3 a_vP1, glm::vec3 a_vP2, glm::vec3 a_vP3)
{
	glm::vec3 vDir1 = glm::normalize(a_vP2 - a_vP1);
	f32 fDis1 = glm::distance(a_vP2, a_vP1);

	glm::vec3 vDir2 = glm::normalize(a_vP3 - a_vP2);
	f32 fDis2 = glm::distance(a_vP3, a_vP2);

	vector<glm::vec3> arr;
	arr.clear();
	arr.push_back(a_vP1);
	for (n32 i = 1; i <= 48; i++)
	{
		f32 fRate = i / 48.0f;
		f32 fDis10 = fDis1 * fRate;
		glm::vec3 vPos10 = vDir1 * fDis10 + a_vP1;


		f32 fDis20 = fDis10 / fDis1 * fDis2;
		glm::vec3 vPos20 = vDir2 * fDis20 + a_vP2;

		glm::vec3 vDir3 = glm::normalize(vPos20 - vPos10);
		f32 fDis3 = glm::distance(vPos20, vPos10);

		f32 fDis30 = fDis10 / fDis1 * fDis3;
		glm::vec3 vPos30 = vDir3 * fDis30 + vPos10;
		arr.push_back(vPos30);
	}
	arr.push_back(a_vP3);
	return arr;
}

T_INLINE glm::mat4 AIMatrixToGLMMatrix(const aiMatrix4x4& mat)
{
	return glm::mat4(mat.a1, mat.b1, mat.c1, mat.d1,
		mat.a2, mat.b2, mat.c2, mat.d2,
		mat.a3, mat.b3, mat.c3, mat.d3,
		mat.a4, mat.b4, mat.c4, mat.d4);
}
