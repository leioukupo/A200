PROJECT(A200_win)
cmake_minimum_required(VERSION 3.10)


# 设置源文件变量
SET(LOCAL_SRC_FILES color_viewer.cpp ./Common/Render.cpp ./Common/Util.cpp)

# 设置头文件搜索路径
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)
include_directories(./Common)
include_directories(../Include/ImiNect)
include_directories(../Include/GL)
# x64
# 设置动态库搜索路径
link_directories(../Redist/x64)

# glut库 ${GLUT_LIBRARIES}
set(GLUT_LIBRARIES ../3rdparty/freeglut-2.8.1/lib/x64/Release)
link_directories(../3rdparty/freeglut-2.8.1/lib/x64/Release)

# gl库 ${OPENGL_LIBRARIES}
if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif ()
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(color_viewer ${LOCAL_SRC_FILES})
target_link_libraries(color_viewer freeglut ${OPENGL_LIBRARIES})

target_link_libraries(color_viewer ImiCamera)
target_link_libraries(color_viewer iminect)



