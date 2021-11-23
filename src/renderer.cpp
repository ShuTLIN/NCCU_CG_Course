#include<renderer.h>

renderer::renderer(loadmodel& model, shader& shader, view& camera , uniformConfig& uniform) {
	shaderObj = &shader;
	modelObj = &model;
	cameraObj = &camera;
	uniformObj = &uniform;

	modelObj->genBuffer();
	vaoID = modelObj->getVao();
	modelObj->bindVao();

	//std::cout << "VAO: " << vaoID << std::endl;
	viewMatrix = cameraObj->getViewMatrix();
	projMatrix = cameraObj->getProjMatrix();
	modelMatrix = modelObj->getModelMatrix();

	//binding shader and get attrib location
	shaderObj->createShader();
	shaderObj->genShaderProgram();
	shaderObj->bindShaderProgram();

	uProjMatrix = shaderObj->getShaderUniformLocation("uProjMatrix");
	uModelMatrix = shaderObj->getShaderUniformLocation("uModelMatrix");
	uViewMatrix = shaderObj->getShaderUniformLocation("uViewMatrix");

	//set all uniform variable value in shader
	shaderObj->initUniform(*uniformObj);
}

renderer::renderer(loadmodel& model , shader& shader, view& camera ) {
	shaderObj = &shader;
	cameraObj = &camera;
	modelObj = &model;

	modelObj->genBuffer();
	vaoID = modelObj->getVao();
	modelObj->bindVao();

	viewMatrix = cameraObj->getViewMatrix();
	projMatrix = cameraObj->getProjMatrix();

	//binding shader and get attrib location
	shaderObj->createShader();
	shaderObj->genShaderProgram();
	shaderObj->bindShaderProgram();

	
	uProjMatrix = shaderObj->getShaderUniformLocation("uProjMatrix");
	uModelMatrix = shaderObj->getShaderUniformLocation("uModelMatrix");
	uViewMatrix = shaderObj->getShaderUniformLocation("uViewMatrix");
}

renderer::~renderer(){

}


void renderer::render() {
	shaderObj->bindShaderProgram();

	//set MVP matrix in buffer
	if (shaderObj->findUniformName("uProjMatrix")) {
		glUniformMatrix4fv(shaderObj->getShaderUniformLocation("uProjMatrix"), 1, GL_FALSE, glm::value_ptr(cameraObj->getProjMatrix()));
	};
	if (shaderObj->findUniformName("uViewMatrix")) {
		glUniformMatrix4fv(shaderObj->getShaderUniformLocation("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(cameraObj->getViewMatrix()));
	};
	if (shaderObj->findUniformName("uModelMatrix")) {
		glUniformMatrix4fv(shaderObj->getShaderUniformLocation("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelObj->getModelMatrix()));
	};


	if (modelObj->getModelType() == "Voxel") {
		renderVoxel();
	}

	if (modelObj->getModelType() == "Vertex") {
		renderVertex();
	}
	if (modelObj->getModelType() == "Obj") {
		renderVertex();
	}
}

void renderer::renderVoxel() {
	modelObj->bindVao();
	//std::cout << modelObj->getVertexNum() << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVertexNum());
	shaderObj->UnBindShaderProgram();
}

void renderer::renderVertex() {
	modelObj->bindVao();
	//std::cout << modelObj->getVertexNum() << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVertexNum());
	shaderObj->UnBindShaderProgram();
}