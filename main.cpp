
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // Configure GLFW (library for easily creating a window).
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window.
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Learn OpenGL", NULL, NULL);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Activate an OpenGL context. This is needed for OpenGL function pointers to have addresses.
    glfwMakeContextCurrent(window);

    // Initialise GLAD. Pass the function that loads the address of OpenGL function pointers.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cerr << "Failed to initialise GLAD." << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);

    // Rendering loop.
    // This is where all rendering commands are executed (i.e., calculating pixel colours)
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering commands here...
        glClearColor(0.97f, 0.79f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

