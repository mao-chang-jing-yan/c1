cmake_minimum_required(VERSION 3.16)
project(c1 C)

set(CMAKE_C_STANDARD 99)

add_executable(c1 main.c header/func.h source/func.c header/graph.h source/graph.c source/qNode.c header/qNode.h header/stack.h source/stack.c header/yiqun.h source/yiqun.c source/window.c header/window.h header/file.h source/file.c header/str.h source/str.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/ext
        )
#包含子模块"yaml-cpp-master"
#add_subdirectory(library/yaml-cpp)
#set(ENV{http_proxy} "http://127.0.0.1:3128")
#set(ENV{https_proxy} "https://127.0.0.1:1086")

#include(FetchContent)
#fetchcontent_declare(ffmpeg #库名字
#        GIT_REPOSITORY https://github.com/FFmpeg/FFmpeg.git # 仓库地址
##        GIT_TAG v2.x # 库版本
#        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/ffmpeg # 指定库下载地址
#        )
#
#fetchcontent_makeavailable(ffmpeg)
#
## 项目中使用spdlog
#target_link_libraries(c1 PRIVATE ffmpeg::ffmpeg)