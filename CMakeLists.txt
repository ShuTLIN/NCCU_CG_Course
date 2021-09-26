
cmake_minimum_required (VERSION 3.8)

project ("NCCU_CG_Course")


add_subdirectory("glew")
add_subdirectory("glfw")
add_subdirectory ("src")


target_include_directories("NCCU_CG_Course" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories("NCCU_CG_Course" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/venders/imgui-1.84)
target_include_directories("NCCU_CG_Course" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_include_directories("NCCU_CG_Course" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)
target_include_directories("NCCU_CG_Course" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)


file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src/shaders)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src/models)

#file(COPY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vshader.glsl ${CMAKE_CURRENT_BINARY_DIR}/src/shaders/vshader.glsl
 #    RESULT first_test
  #   ONLY_IF_DIFFERENT)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/vshader.glsl ${CMAKE_CURRENT_BINARY_DIR}/src/shaders/ COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/fshader.glsl ${CMAKE_CURRENT_BINARY_DIR}/src/shaders/ COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)