#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

///////////////////////////////////////////////////

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>						// glm::v-ec3
#include <glm/vec4.hpp>						// glm::vec4
#include <glm/mat4x4.hpp>					// glm::mat4
#include <glm/gtc/matrix_transform.hpp>		// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>				// glm::value_ptr
#include <glm/gtx/vector_angle.hpp>
#include <FreeImage/FreeImage.h>
#include <rapidjson/document.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

///////////////////////////////////////////////////
#include "../TCore/TCore.h"

