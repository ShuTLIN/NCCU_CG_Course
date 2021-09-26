#include<renderer.h>

renderer::renderer(loadmodel& model, shader& shader, view& camera) {
	shaderObj = &shader;
	modelObj = &model;
	cameraObj = &camera;

	modelObj->genBuffer();
	vaoID = modelObj->getVao();
	//std::cout << "VAO: " << vaoID << std::endl;
	view_proj_matrix = cameraObj->getViewProjMatrix();
	model_matrix = modelObj->getModelMatrix();

	//binding shader and get attrib location
	shaderObj->createShader();
	shaderObj->genShaderProgram();
	shaderObj->bindShaderProgram();

	v_position = shaderObj->getShaderAttribLocation("vPosition");
	v_color = shaderObj->getShaderAttribLocation("vColor");
	u_model_view_matrix = shaderObj->getShaderUniformLocation("uViewProjMatrix");
	u_model_matrix = shaderObj->getShaderUniformLocation("uModelMatrix");
}

renderer::~renderer(){

}


void renderer::render() {

	//std::cout << v_position << " " << v_color << " " << u_model_view_matrix << " " << std::endl;
	/*std::cout << "view_proj_matrix col1  " << view_proj_matrix[0][0] << ' ' << view_proj_matrix[0][1] << " " << view_proj_matrix[0][2] << std::endl;
	std::cout << "view_proj_matrix col2  " << view_proj_matrix[1][0] << ' ' << view_proj_matrix[1][1] << " " << view_proj_matrix[1][2] << std::endl;
	std::cout << "view_proj_matrix col3  " << view_proj_matrix[2][0] << ' ' << view_proj_matrix[2][1] << " " << view_proj_matrix[2][2] << std::endl;
	std::cout << "view_proj_matrix col4  " << view_proj_matrix[3][0] << ' ' << view_proj_matrix[3][1] << " " << view_proj_matrix[3][2] << std::endl;*/

	shaderObj->bindShaderProgram();
	modelObj->bindVao();
	view_proj_matrix = cameraObj->getViewProjMatrix();
	model_matrix = modelObj->getModelMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(u_model_view_matrix, 1, GL_FALSE, glm::value_ptr(view_proj_matrix));
	glUniformMatrix4fv(u_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));

	glDrawElements(GL_TRIANGLES, modelObj->getIndexLen() , GL_UNSIGNED_INT, nullptr);

	shaderObj->UnBindShaderProgram();
}