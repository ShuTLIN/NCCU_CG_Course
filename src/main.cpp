
#include "buttom_handle.hpp"
#include "renderer.h"
#include "ogt_vox.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

void demo_load_and_save(std::string filepath);

//all state logging
extern bool mouseEvent;
extern float mouseScroll;
extern float mouseMiddle_xoffset;
extern float mouseMiddle_yoffset;
extern float mouseRight_xoffset;
extern float mouseRight_yoffset;

GLfloat half_width = 400, half_height = 400, half_depth = 600;

int main(int argc, char** argv) {
    //! The pointer to the GLFW window
    GLFWwindow* window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(Buttom::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
        return -1;

    // We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // ! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(half_width * 2, half_height * 2, "NCCU CG Course OpenGL Template", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // ! Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    // Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW Init Failed : %s" << std::endl;
    }

    // Print and see what context got enabled
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    // Keyboard Callback
    glfwSetKeyCallback(window, Buttom::key_callback);
    // Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, Buttom::framebuffer_size_callback);
    //Mouse Callback
    glfwSetCursorPosCallback(window, Buttom::cursor_position_callback);
    glfwSetMouseButtonCallback(window, Buttom::mouse_button_callback);
    glfwSetScrollCallback(window, Buttom::scroll_callback);
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialize GL state
    Buttom::initGL();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //load shader, model and setting camera
    view camera(45.0f, half_width / half_height, glm::vec3(0.0f, -50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader voxShader("./shaders/vshader.glsl", "./shaders/fshader.glsl");
    loadmodel model("./models/castle.vox");

    //binding all together
    renderer voxel(model, voxShader, camera);

    // Our Imgui state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static float_t localTrans[3] = {0.0f, 0.0f ,0.0f};
    static float_t localRotate[3] = { 0.0f, 0.0f ,0.0f };
    static float_t globalRotate[3] = { 0.0f, 0.0f ,0.0f };
    static float_t localScale[3] = { 1.0f, 1.0f ,1.0f };
    

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0) {

    //listen to mouse event
    if (mouseEvent) {
        camera.updateViewMatrix(mouseScroll, mouseMiddle_xoffset, mouseMiddle_yoffset, mouseRight_xoffset, mouseRight_yoffset);
        mouseEvent = false;
    }
    // Render model here
    voxel.render();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::Begin("Hello, CG");                       
        
        ImGui::SliderFloat3("Local Translate.", &localTrans[0], -100.0f, 100.0f);           
        ImGui::SliderFloat3("Local Rotate.", &localRotate[0], -360.0f, 360.0f);
        ImGui::SliderFloat3("Local Scale.", &localScale[0], 1.0f, 10.0f);
        ImGui::SliderFloat3("Global Rotate.", &globalRotate[0], -360.0f, 360.0f);

        model.localTranslate(localTrans[0], localTrans[1], localTrans[2]);
        model.localRotate(localRotate[0], localRotate[1], localRotate[2]);
        model.localScale(localScale[0], localScale[1], localScale[2]);
        model.globalRotate(globalRotate[0], globalRotate[1], globalRotate[2]);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    //Imgui Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}
