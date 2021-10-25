#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <vector>
#include <cmath>
#include <string>

#include "buttom_handle.hpp"
#include "shader.h"
#include "loadmodel.h"

class view {
 public:
  view();
  view(float_t view_ratio, float_t width_height_ratio, glm::vec3 camera_pos, glm::vec3 camera_lookat, glm::vec3 camera_up);
  void updateViewMatrix(float_t mouseScroll, float_t mouseMiddle_xoffset, float_t mouseMiddle_yoffset, float_t mouseRight_xoffset, float_t mouseRight_yoffset);
  void printVec(glm::vec3 vec);
  void printVec(glm::vec4 vec);
  void printMatrix(glm::mat4 matrix);
  void printMatrix(glm::mat3 matrix);
  glm::vec3 getViewSpaceXaxis();
  glm::vec3 getViewSpaceYaxis();
  glm::vec3 getViewSpaceZaxis();
  glm::mat4 getViewMatrix();
  glm::mat4 getProjMatrix();

 private:
  float_t scrollFactor;
  float_t offsetFactor;
  glm::vec3 cameraPosition;
  glm::vec3 cameraLookDir;
  glm::vec3 cameraUp;
  glm::vec3 cameraXoffset;
  glm::vec3 cameraYoffset;
 
  float_t nearPlane;
  float_t farPlane;
  float_t oldMouseScroll;
  float_t oldMouseMiddleXoffset;
  float_t oldMouseMiddleYoffset;

  glm::mat4 orthoMatrix;
  glm::mat4 perspMatrix;
  glm::mat4 lookAtMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 projMatrix;

  glm::vec3 viewspaceXaxis;
  glm::vec3 viewspaceYaxis;
  glm::vec3 viewspaceZaxis;
};

#endif  // VIEW_HPP_
