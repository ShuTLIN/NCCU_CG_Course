# CMakeList.txt: CMakeProject1 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)


add_executable (NCCU_CG_Course  "main.cpp" 
"check.cpp"
"buttom_handle.cpp"
"demo_vox.cpp"
"loadmodel.cpp"
"renderer.cpp"
"shader.cpp"
"view.cpp"
"uniformConfig.cpp"
"../venders/imgui-1.84/imgui.cpp"
"../venders/imgui-1.84/imgui_demo.cpp"
"../venders/imgui-1.84/imgui_draw.cpp"
"../venders/imgui-1.84/imgui_impl_glfw.cpp"
"../venders/imgui-1.84/imgui_impl_opengl3.cpp"
"../venders/imgui-1.84/imgui_tables.cpp"
"../venders/imgui-1.84/imgui_widgets.cpp"
)

target_link_libraries(NCCU_CG_Course
	glfw
	libglew_static
)