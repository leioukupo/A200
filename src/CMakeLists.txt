PROJECT (color_viewer)
cmake_minimum_required(VERSION 3.10)
# 设置源文件变量
SET(LOCAL_SRC_FILES main.cpp ../Common/Render.cpp ../Common/Util.cpp )
# 设置头文件搜索路径
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)
include_directories(../Common)
include_directories(../../../include)

# 设置动态库搜索路径
link_directories(../../../libs)

# glut库 ${GLUT_LIBRARIES}
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

# gl库 ${OPENGL_LIBRARIES}
if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(color_viewer ${LOCAL_SRC_FILES})
target_link_libraries(color_viewer ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(color_viewer ImiCamera)
target_link_libraries(color_viewer iminect)