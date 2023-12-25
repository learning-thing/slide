cmake_minimum_required(VERSION 3.5.0)
project(slide )

include(CTest)
enable_testing()

add_executable(slide main.cpp)
target_link_libraries(slide raylib)


add_executable(loading loading.cpp)
target_link_libraries(loading raylib)


add_executable(pong pong.cpp)
target_link_libraries(pong raylib)


add_executable(PI Pi.cpp)
target_link_libraries(PI raylib)

add_executable(dvd dvd.cpp)
target_link_libraries(dvd raylib)

add_executable(3d movement.cpp)
target_link_libraries(3d raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

