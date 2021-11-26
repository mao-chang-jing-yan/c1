cmake_minimum_required(VERSION 3.16)
project(c1 C)

set(CMAKE_C_STANDARD 99)

add_executable(c1 main.c header/func.h source/func.c header/graph.h source/graph.c source/qNode.c header/qNode.h header/stack.h source/stack.c test.c header/yiqun.h source/yiqun.c source/window.c header/window.h)