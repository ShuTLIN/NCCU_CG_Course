#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

struct shaderSourceID {
	uint32_t vertexShaderID;
	uint32_t fragShaderID;
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

	uint32_t getShaderAttribLocation(const char* parameter);
	uint32_t getShaderUniformLocation( const char* parameter);
private:
	uint32_t shaderProgramID;
	shaderSourceID shaderID;
	std::string vertexShader;
	std::string fragShader;
};
