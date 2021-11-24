#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <uniformConfig.h>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#define BUFFER_OFFSET(offset) (reinterpret_cast<void *>(offset))

struct shaderSourceID {
	uint32_t vertexShaderID;
	uint32_t fragShaderID;
};

struct uniformProp {
	std::string name;
	uint32_t index;
	uint32_t type;
	uint32_t size=0;
};

struct attribProp {
	std::string name;
	uint32_t index;
};

class shader {
public:
	shader();
	shader(const std::string& vertexShaderPath, const std::string& fragShaderPath);
	~shader();
	void createShader();
	void compileShader(uint32_t shaderID ,std::string shaderSource, GLenum shaderType);
	void genShaderProgram();
	void bindShaderProgram();
	void UnBindShaderProgram();
	void printShaderContent();
	void setCamUniformLocation(glm::mat4* matrix);
	
	void initUniform(uniformConfig& uniform);
	bool findUniformName(const std::string& name);

	std::vector<uniformProp> getUniformInfo();
	uint32_t getShaderAttribLocation(const char* parameter);
	uint32_t getShaderUniformLocation( const char* parameter);
	uint32_t getUniformBifferSize();
private:
	void setVertexAttrib();
	void setUniformBuffer();
	bool attribSet = false;
	bool uniformSet = false;
	uint32_t shaderProgramID;
	uint32_t uniformBufferSize;
	shaderSourceID shaderID;
	std::string vertexShader;
	std::string fragShader;
	std::vector<uniformProp> uniformPropsList;
	std::vector<attribProp> attribPropList;
	void* uniformBuffer;
};
