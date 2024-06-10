cmake_minimum_required(VERSION 3.10)
PROJECT(A200_win)



# 设置源文件变量
SET(Color_SRC color_viewer.cpp ./Common/Render.cpp ./Common/Util.cpp)

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
# color_viewer
add_executable(color_viewer ${Color_SRC})
target_link_libraries(color_viewer freeglut ${OPENGL_LIBRARIES})
target_link_libraries(color_viewer ImiCamera)
target_link_libraries(color_viewer iminect)
# DepthViewer
SET(Depth_SRC DepthViewer.cpp ./Common/Render.cpp ./Common/Util.cpp)
add_executable(depth_viewer ${Depth_SRC})
target_link_libraries(depth_viewer freeglut ${OPENGL_LIBRARIES})
target_link_libraries(depth_viewer ImiCamera)
target_link_libraries(depth_viewer iminect)
# PointCloudViewer
SET(PointCloudViewer_SRC PointCloudViewer.cpp ./Common/Render2.cpp ./Common/Util.h)
add_executable(point_viewer ${PointCloudViewer_SRC})
target_link_libraries(point_viewer freeglut ${OPENGL_LIBRARIES})
target_link_libraries(point_viewer ImiCamera)
target_link_libraries(point_viewer iminect)
# 单路流
## 打开普通彩色深度红外图像
SET(test_SRC open_signal_steam.cpp ./Common/Render.cpp ./Common/Util.cpp)
#SET(test_SRC test.cpp ./Common/Render.cpp ./Common/Util.cpp)
add_executable(test ${test_SRC})
target_link_libraries(test freeglut ${OPENGL_LIBRARIES})
target_link_libraries(test ImiCamera)
target_link_libraries(test iminect)
## 打开UVC彩色图像
SET(UVC_SRC open_uvc_camera.cpp ./Common/Render.cpp ./Common/Util.cpp)
add_executable(UVC ${UVC_SRC})
target_link_libraries(UVC freeglut ${OPENGL_LIBRARIES})
target_link_libraries(UVC ImiCamera)
target_link_libraries(UVC iminect)
