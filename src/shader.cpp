#include<shader.h>

shader::shader(const std::string& vertexShaderPath, const std::string& fragShaderPath) {
	std::ifstream vertex(vertexShaderPath);
	std::ifstream fragment(fragShaderPath);
	
	std::stringstream vertexSource;
	std::stringstream fragmentSource;

	std::string line;
	while (getline(vertex, line)) {
		vertexSource << line << "\n";

		if (line.find("uniform") != std::string::npos) {

			//erase semicolon and find uniform variable name
			line = line.erase(line.length() - 1, line.length());
			while (line.find(" ") != std::string::npos) {
				line = line.substr(line.find(" ") + 1, line.length());
			}

			uniformProp uniformInfo;
			uniformInfo.name = line;
			uniformPropsList.push_back(uniformInfo);
			//std::cout <<"Vertex uniform: " << line << std::endl;
		}

		if (line.find("layout") != std::string::npos) {
			attribProp attrib;

			//remove all space
			std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());

			//erase semicolon and find uniform variable name
			line.erase(line.length() - 1, line.length());

			std::string varName = line;
			varName.erase(0 , line.find("v_"));
			attrib.name = varName;
			//std::cout << "vertex attribute name: " << varName << " | ";

			std::string location = line;
			int32_t leftParenthesis = location.find("(");
			int32_t rightParenthesis = location.find(")") - line.find("(");
			location = location.substr(leftParenthesis + 1, rightParenthesis-1);
			location = location.substr(location.find("=") + 1, location.find("=") + 2);

			
			if (stoi(location) == -1) {
				std::cout << "not get correct vertex attribute location: "<<std::endl;
			}
			else {
				uint32_t idx = stoi(location);
				attrib.index = idx;
			}

			attribPropList.push_back(attrib);
			//std::cout << "vertex attribute location: " << line << std::endl;
		}
	}

	while (getline(fragment, line)) {
		fragmentSource << line << "\n";	


		if (line.find("uniform") != std::string::npos) {

			//erase semicolon and find uniform variable name
			line = line.erase(line.length() - 1, line.length());
			while (line.find(" ") != std::string::npos) {
				line = line.substr(line.find(" ") + 1, line.length());
			}

			uniformProp uniformInfo;
			uniformInfo.name = line;
			uniformPropsList.push_back(uniformInfo);
			//std::cout << "Fragment uniform: " << line << std::endl;
		}
	}

	vertexShader = vertexSource.str();
	fragShader = fragmentSource.str();
}


shader::shader() {

}

shader::~shader() {

}

void shader::createShader(){
	uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	shaderID= { vertexShaderID ,fragShaderID };
}

void shader::compileShader(uint32_t shaderID,std::string shaderSource,GLenum shaderType) {
	const char* Source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &Source, nullptr);
	glCompileShader(shaderID);
	//std::cout << Source << std::endl;
	int32_t result;
	glGetShaderiv(shaderID , GL_COMPILE_STATUS , &result);
	if (result == GL_FALSE) {
		int32_t length;
		glGetShaderiv(shaderID , GL_INFO_LOG_LENGTH , &length);
		char* message = (char*)alloca(length*sizeof(char));
		glGetShaderInfoLog(shaderID , length , &length , message);

		std::string Type;
		if (shaderType == GL_VERTEX_SHADER) Type = "vertexShader";
		if (shaderType == GL_FRAGMENT_SHADER) Type = "fragShader";
		std::cout << Type << " Failure Compile:" << message << std::endl;

		glDeleteShader(shaderID);
	}
}

void shader::genShaderProgram() {

	shaderProgramID = glCreateProgram();

	compileShader(shaderID.vertexShaderID, vertexShader, GL_VERTEX_SHADER);
	compileShader(shaderID.fragShaderID, fragShader, GL_FRAGMENT_SHADER);

	glAttachShader(shaderProgramID, shaderID.vertexShaderID);
	glAttachShader(shaderProgramID, shaderID.fragShaderID);

	glLinkProgram(shaderProgramID);

	GLint status;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, strInfoLog);
		std::cerr << "GLSL Linker failure: " << strInfoLog << std::endl;
		delete[] strInfoLog;
	}

	glValidateProgram(shaderProgramID);
}

void shader::bindShaderProgram() {
	glUseProgram(shaderProgramID);

	//if first binding shader,then set all uniform variable
	if (!uniformSet) {
		setUniformBuffer();
		uniformSet = true;
	}

	if (!attribSet) {
		setVertexAttrib();
		attribSet = true;
	}
	//std::cout << shaderProgramID << std::endl;
}

void shader::UnBindShaderProgram(){
	glUseProgram(0);
}

void shader::printShaderContent() {
	std::cout << vertexShader << std::endl;
	std::cout << fragShader << std::endl;
}

uint32_t shader::getUniformBifferSize() {
	return uniformBufferSize;
}

std::vector<uniformProp> shader::getUniformInfo() {
	return uniformPropsList;
}

void shader::initUniform(uniformConfig& uniform) {
	std::vector<std::string> uniformName= uniform.getUniformList();
	std::vector<void*> uniformDataPtr= uniform.getUniformDataPtrList();
	
	uint32_t offsetByte = 0;
	for (int i = 0; i < uniformName.size(); i++) {
		for (auto& uniformList : uniformPropsList) {
			if (uniformName[i].compare(uniformList.name) == 0) {

				bindShaderProgram();
				if (uniformList.type == GL_FLOAT_VEC3  ) {
					std::cout << "Uniform name: " << uniformList.name << "    Type: GL_FLOAT_VEC3     " \
						"Size:  " << uniformList.size << std::endl;
					//std::cout << "current offset byte: " << offsetByte << std::endl;
					memcpy((char*)uniformBuffer + offsetByte, (uniformDataPtr[i]), uniformList.size);
					
					glUniform3fv(uniformList.index, 1, (float*)((char*)uniformBuffer + offsetByte));
				}
				else if (uniformList.type == GL_FLOAT) {
					std::cout << "Uniform name: " << uniformList.name << "    Type: GL_FLOAT     " \
						"Size:  " << uniformList.size << std::endl;
					//std::cout << "current offset byte: " << offsetByte << std::endl;
					memcpy((char*)uniformBuffer + offsetByte, (uniformDataPtr[i]), uniformList.size);
					 
					glUniform1fv(uniformList.index, 1, (float*)((char*)uniformBuffer + offsetByte));
				}

			}

			offsetByte += uniformList.size;
		}
		
	}
}

uint32_t shader::getShaderAttribLocation( const char* parameter) {
	return glGetAttribLocation(shaderProgramID, parameter);
}

uint32_t shader::getShaderUniformLocation( const char* parameter) {
	return glGetUniformLocation(shaderProgramID, parameter);
}

void shader::setCamUniformLocation(glm::mat4* matrix) {

};

bool shader::findUniformName(const std::string& name) {
	for (auto& element : uniformPropsList) {
		if (element.name.find(name) != std::string::npos) {
			//std::cout << "Find uniform name: " << element.name << std::endl;
			return true;
		}
	}
}

void shader::setVertexAttrib() {
	uint32_t offset = 0;
	
	for (auto& element : attribPropList) {
		const char* n = element.name.c_str();
		glEnableVertexAttribArray(element.index);
		glVertexAttribPointer(getShaderAttribLocation(element.name.c_str()), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float) * attribPropList.size() , BUFFER_OFFSET(offset));
		offset += sizeof(glm::vec4);

		//std::cout << getShaderAttribLocation(element.name.c_str()) <<" | "<< element.name.c_str() << " | " << offset << std::endl;
	}
}

void shader::setUniformBuffer() {
	int32_t size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const uint32_t bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	int32_t  length; // name length
	uint32_t BufferSize = 0;

	for (auto& element : uniformPropsList) {
		uint32_t uniformIndex = getShaderUniformLocation(element.name.c_str());
		element.index = uniformIndex;
		
		//get uniform variable data type
		glGetActiveUniform(shaderProgramID, uniformIndex, bufSize, &length, &size, &type, name);
		//std::cout << type << std::endl;
		element.type = type;
		switch (type) {
		case GL_FLOAT_VEC3:
			//std::cout << "float vec3" << std::endl;
			element.size = 4 * 3;
			BufferSize += element.size;
			break;
		case GL_FLOAT:
			//std::cout << "float" << std::endl;
			element.size = 4;
			BufferSize += element.size;
			break;
		case GL_FLOAT_MAT4:
			element.size = 4 * 4 * 4;
			BufferSize += element.size;
			break;
		default:
			std::cout << "Not find property type match  "<< element .name<<"  this uniform data type" << std::endl;
			break;
		}
		/*std::cout << "shader uniform: " << element.name << std::endl;
		std::cout << "Index: " << uniformIndex << std::endl;
		std::cout << "Uniform DataBuffer Size: " << BufferSize << " bytes" << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;*/
	}

	uniformBufferSize = BufferSize;
	uniformBuffer = (void*)malloc(uniformBufferSize);
};

