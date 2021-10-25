#include "buttom_handle.hpp"

//all state logging
bool mouseEvent = false;
float mouseScroll = 0.0;
float mouseMiddle_xoffset = 0.0;
float mouseMiddle_yoffset = 0.0;
float mouseRight_xoffset = 0.0;
float mouseRight_yoffset = 0.0;
int rightHoldCount=0;
int middleHoldCount = 0;
float mouseOldXpos;
float mouseOldYpos;

namespace Buttom {

  // !Initialize GL State
  void initGL(void) {
    // Set frame buffer clear color
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    // Set depth buffer furthest depth
    glClearDepth(1.0);
    // Set depth test to less-than
    glDepthFunc(GL_LESS);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    // Enable Gourard shading
    glShadeModel(GL_SMOOTH);
  }

  // !GLFW Error Callback
  void error_callback(int error, const char* description) {
    std::cerr << description << std::endl;
  }

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

      int rightclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
      int middleclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
      
      if (rightclick == GLFW_PRESS)
      {
          mouseEvent = true;
          if (rightHoldCount == 0) {
              mouseOldXpos = xpos;
              mouseOldYpos = ypos;
          }

      
          mouseRight_xoffset += xpos - mouseOldXpos;
          if (mouseRight_xoffset > 89.0f) {
              mouseRight_xoffset = 89.0f;
          }
          else if (mouseRight_xoffset < -89.0f) {
              mouseRight_xoffset = -89.0f;
          }

          mouseRight_yoffset += ypos - mouseOldYpos;
          if (mouseRight_yoffset > 89.0f) {
              mouseRight_yoffset = 89.0f;
          }
          else if (mouseRight_yoffset < -89.0f) {
              mouseRight_yoffset = -89.0f;
          }
 
          mouseOldXpos = xpos;
          mouseOldYpos = ypos;
          //std::cout << "mouseRight_xoffset" << mouseRight_xoffset << "mouseRight_yoffset" << mouseRight_yoffset << std::endl;
          rightHoldCount++;
      }
      else if (rightclick == GLFW_RELEASE && middleclick == GLFW_RELEASE) {
          rightHoldCount = 0;
          mouseEvent = false;
      }
      

      if (middleclick == GLFW_PRESS)
      {
          mouseEvent = true;
          if (middleHoldCount == 0) {
              mouseOldXpos = xpos;
              mouseOldYpos = ypos;
          }

          mouseMiddle_xoffset += xpos - mouseOldXpos;
          mouseMiddle_yoffset += ypos - mouseOldYpos;

          mouseOldXpos = xpos;
          mouseOldYpos = ypos;
          //std::cout << "mouseMiddle_xoffset" << mouseMiddle_xoffset << "mouseMiddle_yoffset" << mouseMiddle_yoffset << std::endl;
          middleHoldCount++;
      }
      else if (rightclick == GLFW_RELEASE && middleclick == GLFW_RELEASE) {
          mouseEvent = false;
          middleHoldCount = 0;
      }
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
 
  }

  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
  {
      mouseEvent = true;
      mouseScroll += yoffset;
  }

  // !GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // !Resize the view port to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  // !GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // !Close the window if the ESC key was pressed
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  }
};  
