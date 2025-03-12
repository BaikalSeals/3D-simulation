cmake_minimum_required(VERSION 3.22)
project(myProject)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*.c")
file(GLOB HEADERS "include/*.h" "include/stb/stb_image.h")


add_executable(myProject
	${SOURCES}
	${HEADERS}
)

target_link_libraries(myProject
	glfw
	OpenGL::GL
	glm::glm
)
