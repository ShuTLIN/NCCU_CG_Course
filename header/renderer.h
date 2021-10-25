#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <uniformConfig.h>
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
	renderer(loadmodel& model , shader& shader , view& camera , uniformConfig& uniform);
	renderer(loadmodel& model ,shader& shader, view& camera );
	~renderer();
	void render();
	
private:
	void renderVoxel();
	void renderVertex();

	shader* shaderObj;
	loadmodel* modelObj;
	view* cameraObj;
	uniformConfig* uniformObj;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;

	uint32_t vaoID;
	uint32_t vboID;
	uint32_t uProjMatrix;
	uint32_t uModelMatrix;
	uint32_t uViewMatrix;

};
