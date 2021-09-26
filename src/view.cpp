#include "view.hpp"
view::view(float_t view_ratio, float_t width_height_ratio, glm::vec3 pos, glm::vec3 lookat, glm::vec3 up) {
	
	//Setup and initialize all camera needs
	scroll_factor = 1.0f;
	offset_factor = 0.01f;
	camera_position = pos;
	camera_up = up;

	persp_matrix = glm::perspective(glm::radians(view_ratio), width_height_ratio, 1.0f, 300.0f);
	lookAt_matrix = glm::lookAt(camera_position, lookat, camera_up);
	view_proj_matrix = persp_matrix * lookAt_matrix;

	viewspaceZaxis = glm::normalize(camera_position);
	viewspaceXaxis = glm::normalize(glm::cross(-viewspaceZaxis, camera_up));
	viewspaceYaxis = glm::normalize(glm::cross(viewspaceXaxis, -viewspaceZaxis));

	camera_lookDir = -viewspaceZaxis;
	camera_xoffset = viewspaceXaxis;
	camera_yoffset = viewspaceYaxis;
};

view::view() {

};


void view::updateViewMatrix(float_t mouseScroll , float_t mouseMiddle_xoffset, float_t mouseMiddle_yoffset, float_t mouseRight_xoffset,float_t mouseRight_yoffset) {
	glm::vec3 update_position = camera_position;
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

		camera_lookDir = viewDir;
		camera_xoffset = glm::vec3(rotateXaxis);
		camera_yoffset = glm::vec3(rotateYaxis);

	}
	if (mouseScroll != 0.0) {
		update_position += mouseScroll * scroll_factor * camera_lookDir;
	}
	if (mouseMiddle_xoffset != 0.0) {
		update_position += mouseMiddle_xoffset * offset_factor * -camera_xoffset;
	}
	if (mouseMiddle_yoffset != 0.0) {
		update_position += -mouseMiddle_yoffset * offset_factor * -camera_yoffset;
	}
	
	glm::mat4 viewTrans=glm::mat4(1.0f);
	viewTrans[3] = glm::vec4(-update_position,1.0f);
	view = glm::transpose(view);
	lookAt_matrix = view * viewTrans ;
	view_proj_matrix = persp_matrix * lookAt_matrix;
};

glm::mat4 view::getViewProjMatrix() {
	return view_proj_matrix;
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

