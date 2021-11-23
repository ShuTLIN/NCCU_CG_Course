#include "view.hpp"
view::view(float_t view_ratio, float_t width_height_ratio, glm::vec3 pos, glm::vec3 lookat, glm::vec3 up) {
	
	//Setup and initialize all camera needs
	scrollFactor = 1.0f;
	offsetFactor = 0.01f;
	cameraPosition = pos;
	cameraUp = up;


	nearPlane = 1.0f;
	farPlane = 300.0f;
	perspMatrix = glm::perspective(glm::radians(view_ratio), width_height_ratio, 0.1f, 300.0f);
	lookAtMatrix = glm::lookAt(cameraPosition, lookat, cameraUp);
	
	viewMatrix = lookAtMatrix;
	projMatrix = perspMatrix;

	viewspaceZaxis = glm::normalize(cameraPosition);
	viewspaceXaxis = glm::normalize(glm::cross(-viewspaceZaxis, cameraUp));
	viewspaceYaxis = glm::normalize(glm::cross(viewspaceXaxis, -viewspaceZaxis));

	cameraLookDir = -viewspaceZaxis;
	cameraXoffset = viewspaceXaxis;
	cameraYoffset = viewspaceYaxis;

	oldMouseScroll = 0.0;
	oldMouseMiddleXoffset = 0.0;
	oldMouseMiddleYoffset = 0.0;
};

view::view() {

};


void view::updateViewMatrix(float_t mouseScroll , float_t mouseMiddle_xoffset, float_t mouseMiddle_yoffset, float_t mouseRight_xoffset,float_t mouseRight_yoffset) {
	glm::mat4 view = glm::mat4(glm::vec4(viewspaceXaxis, 0.0f), glm::vec4(viewspaceYaxis, 0.0f), glm::vec4(viewspaceZaxis, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	if (mouseRight_xoffset != 0.0 || mouseRight_yoffset != 0.0) {
		float_t dirX = glm::sin(glm::radians(mouseRight_xoffset)) * glm::cos(glm::radians(mouseRight_yoffset));
		float_t dirY = -glm::sin(glm::radians(mouseRight_yoffset));
		float_t dirZ = -glm::cos(glm::radians(mouseRight_xoffset)) * glm::cos(glm::radians(mouseRight_yoffset));
		glm::vec3 viewDir=glm::normalize(dirX * viewspaceXaxis + dirY * viewspaceYaxis + dirZ * viewspaceZaxis);

		glm::vec4 rotateXaxis = glm::vec4(glm::normalize(glm::cross(viewDir,viewspaceYaxis)),0.0f);
		glm::vec4 rotateYaxis = glm::vec4(glm::normalize(glm::cross(glm::vec3(rotateXaxis), viewDir)),0.0f);
		glm::vec4 rotateZaxis = glm::vec4(glm::normalize(glm::cross(glm::vec3(rotateXaxis), glm::vec3(rotateYaxis))),0.0f);

		view[0] = rotateXaxis;
		view[1] = rotateYaxis;
		view[2] = rotateZaxis;

		cameraLookDir = viewDir;
		cameraXoffset = glm::vec3(rotateXaxis);
		cameraYoffset = glm::vec3(rotateYaxis);

	}
	if ( (oldMouseScroll - mouseScroll) != (float_t)0.0) {
		cameraPosition += -(oldMouseScroll - mouseScroll) * cameraLookDir;
		oldMouseScroll = mouseScroll;
	}
	if ( (oldMouseMiddleXoffset- mouseMiddle_xoffset) != (float_t)0.0) {
		cameraPosition += -(oldMouseMiddleXoffset - mouseMiddle_xoffset) * offsetFactor * -cameraXoffset;
		oldMouseMiddleXoffset = mouseMiddle_xoffset;
	}
	if ( (oldMouseMiddleYoffset - mouseMiddle_yoffset) != (float_t)0.0) {
		cameraPosition += (oldMouseMiddleYoffset - mouseMiddle_yoffset) * offsetFactor * -cameraYoffset;
		oldMouseMiddleYoffset = mouseMiddle_yoffset;
	}

	glm::mat4 viewTrans=glm::mat4(1.0f);
	viewTrans[3] = glm::vec4(-cameraPosition,1.0f);
	view = glm::transpose(view);
	lookAtMatrix = view * viewTrans ;

	viewMatrix = lookAtMatrix;
	projMatrix = perspMatrix;
};

glm::mat4 view::getViewMatrix() {
	return viewMatrix;
};

glm::mat4 view::getProjMatrix() {
	return projMatrix;
};


glm::vec3 view::getViewSpaceXaxis() {
	return viewspaceXaxis;
};
glm::vec3 view::getViewSpaceYaxis() {
	return viewspaceYaxis;
};
glm::vec3 view::getViewSpaceZaxis() {
	return viewspaceZaxis;
};

glm::vec3 view::getCameraPos() {
	return cameraPosition;
};

glm::vec3 view::getCameraLookDir() {
	return cameraLookDir;
};

void view::printVec(glm::vec3 vec) {
	std::cout << "vec3  " << vec.x << ' ' << vec.y << " " << vec.z << std::endl;
};

void view::printVec(glm::vec4 vec) {
	std::cout << "vec4  " << vec.x << ' ' << vec.y << " " << vec.z << " " << vec.w << std::endl;
};

void view::printMatrix(glm::mat4 matrix) {
	std::cout << "Matrix4 col1   " << matrix[0][0] << "  " << matrix[0][1] << "  " << matrix[0][2] << "  " << matrix[0][3] << std::endl;
	std::cout << "Matrix4 col2   " << matrix[1][0] << "  " << matrix[1][1] << "  " << matrix[1][2] << "  " << matrix[1][3] << std::endl;
	std::cout << "Matrix4 col3   " << matrix[2][0] << "  " << matrix[2][1] << "  " << matrix[2][2] << "  " << matrix[2][3] << std::endl;
	std::cout << "Matrix4 col4   " << matrix[3][0] << "  " << matrix[3][1] << "  " << matrix[3][2] << "  " << matrix[3][3] << std::endl;
};

void view::printMatrix(glm::mat3 matrix) {
	std::cout << "Matrix3 col1   " << matrix[0][0] << "  " << matrix[0][1] << "  " << matrix[0][2] << std::endl;
	std::cout << "Matrix3 col2   " << matrix[1][0] << "  " << matrix[1][1] << "  " << matrix[1][2] << std::endl;
	std::cout << "Matrix3 col3   " << matrix[2][0] << "  " << matrix[2][1] << "  " << matrix[2][2] << std::endl;
};