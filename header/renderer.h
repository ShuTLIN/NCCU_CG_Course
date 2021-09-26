#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<loadmodel.h>
#include<shader.h>
#include<view.hpp>
#include<iostream>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

class renderer {
public:
	renderer(loadmodel& model , shader& shader , view& camera);
	~renderer();
	void render();
private:
	shader* shaderObj;
	loadmodel* modelObj;
	view* cameraObj;

	glm::mat4 view_proj_matrix;
	glm::mat4 model_matrix;

	uint32_t vaoID;
	uint32_t v_position;
	uint32_t v_color;
	uint32_t u_model_view_matrix;
	uint32_t u_model_matrix;
};
