cmake_minimum_required(VERSION 3.11)
project(Raycasting)

include(FetchContent)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

# # This is the main part:
add_subdirectory(lib/raylib)
add_executable(${PROJECT_NAME} src/main.cpp )
include_directories(include)
target_link_libraries(${PROJECT_NAME} raylib)

#add_executable(${PROJECT_NAME} src/main.cpp)
#
##add_library(raylib STATIC IMPORTED)
##set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
###set_target_properties(raylib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ./src/)
##target_link_libraries(${PROJECT_NAME} raylib)
#
#target_link_directories(${PROJECT_NAME} PUBLIC lib/)
#target_link_libraries(${PROJECT_NAME} raylib)

