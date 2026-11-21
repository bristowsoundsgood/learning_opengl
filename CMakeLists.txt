cmake_minimum_required(VERSION 4.0.2)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME learning_opengl)
set(GLFW_LIBRARY_NAME glfw)

set(GLAD_ROOT "C:/Users/Joe/Desktop/Graphics/Installs/glad")

project(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
        ${GLFW_LIBRARY_NAME}
        SOURCE_DIR "C:/Users/Joe/Desktop/Graphics/Installs/glfw-3.5.1"
)

FetchContent_MakeAvailable(${GLFW_LIBRARY_NAME})

set(SOURCE_FILES
        main.cpp
        ${GLAD_ROOT}/src/glad.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Do not need to FetchContent for GLAD, because the files are already generated / no CMakeLists.txt exists in the include.
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_ROOT}/include)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY_NAME})