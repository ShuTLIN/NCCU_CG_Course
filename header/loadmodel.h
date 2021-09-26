#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<vector>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#define BUFFER_OFFSET(offset) (reinterpret_cast<void *>(offset))

struct databuffer {
	glm::vec4 vertexPos;
	glm::vec4 vertexColor;
};

struct vec3 {
	float x;
	float y;
	float z;
};

struct voxel_record {
	int32_t x_dimension;
	int32_t y_dimension;
	int32_t z_dimension;
	uint32_t total_voxels;
	std::vector<vec3> colors;
};

class loadmodel {
public:
	loadmodel();
	loadmodel(const std::string& voxelModelFilepath);
	~loadmodel();
	void genBuffer();
	void bindVao();
	void printVoxelRecord();
	void genOneVoxeldata(int32_t x, int32_t y, int32_t z, int32_t voxel_index, vec3 color);
	void localTranslate(float_t x, float_t y, float_t z );
	void localScale(float_t x, float_t y, float_t z);
	void localRotate(float_t x, float_t y, float_t z);
	void globalRotate(float_t x, float_t y, float_t z);

	uint32_t getVao();
	uint32_t getBufferLen();
	uint32_t getIndexLen();
	uint32_t getIbo();
	glm::mat4 getModelMatrix();
private:
	uint32_t vao;
	uint32_t vbo;
	uint32_t ibo;
	std::vector<databuffer> modeldata;
	std::vector<uint32_t> indexdata;

	glm::mat4 modelMatrix;
	glm::mat4 localTranslateMatrix;
	glm::mat4 localRotateMatrix;
	glm::mat4 localScaleMatrix;
	glm::mat4 globalRotateMatrix;

	voxel_record voxel_model;
};