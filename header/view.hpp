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
  glm::mat4 getViewProjMatrix();

 private:
  float_t scroll_factor;
  float_t offset_factor;
  glm::vec3 camera_position;
  glm::vec3 camera_lookDir;
  glm::vec3 camera_up;
  glm::vec3 camera_xoffset;
  glm::vec3 camera_yoffset;
 

  float_t view_ratio;
  float_t width_height_ratio;
  float_t mouse_middle_xRecord;
  float_t mouse_middle_yRecord;

  uint32_t v_position;
  uint32_t v_color;
  uint32_t u_model_view_matrix;

  glm::mat4 ortho_matrix;
  glm::mat4 view_proj_matrix;
  glm::mat4 persp_matrix;
  glm::mat4 lookAt_matrix;

  glm::vec3 viewspaceXaxis;
  glm::vec3 viewspaceYaxis;
  glm::vec3 viewspaceZaxis;
};

#endif  // VIEW_HPP_
