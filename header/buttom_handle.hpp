#ifndef GL_FRAMEWORK_HPP_
#define GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Buttom {
  void initGL(void);
  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  void error_callback(int error, const char* description);
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};  

#endif  // GL_FRAMEWORK_HPP_
