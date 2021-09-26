#include<shader.h>

shader::shader(const std::string& vertexShaderPath, const std::string& fragShaderPath) {
	std::ifstream vertex(vertexShaderPath);
	std::ifstream fragment(fragShaderPath);
	
	std::stringstream vertexSource;
	std::stringstream fragmentSource;

	std::string line;
	while (getline(vertex, line)) {
		vertexSource << line << "\n";
	}
	while (getline(fragment, line)) {
		fragmentSource << line << "\n";
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
	//std::cout << shaderProgramID << std::endl;
}

void shader::UnBindShaderProgram(){
	glUseProgram(0);
}

void shader::printShaderContent() {
	std::cout << vertexShader << std::endl;
	std::cout << fragShader << std::endl;
}

uint32_t shader::getShaderAttribLocation( const char* parameter) {
	return glGetAttribLocation(shaderProgramID, parameter);
}

uint32_t shader::getShaderUniformLocation( const char* parameter) {
	return glGetUniformLocation(shaderProgramID, parameter);
}