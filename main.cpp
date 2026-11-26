#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <math.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

std::string loadShaderSource(const char* filename);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Configure GLFW (library for easily creating a window).
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window.
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", NULL, NULL);
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

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ==== shaders ====
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSrc = loadShaderSource("C:/Users/Joe/Desktop/Graphics/Projects/learning_opengl/Shaders/vertex_core.glsl");
    const GLchar* vertShader = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed." << '\n' << infoLog << std::endl;
        return -1;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSrc = loadShaderSource("C:/Users/Joe/Desktop/Graphics/Projects/learning_opengl/Shaders/fragment_core.glsl");
    const GLchar* fragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed." << '\n' << infoLog << std::endl;
        return -1;
    }

    // Create shader programs
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ==== defining triangle coords ====
    constexpr float triangle[] = {
        // positions        // colours
        -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // ==== loading triangle data into OpenGL ===
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Rendering loop.
    // This is where all rendering commands are executed (i.e., calculating pixel colours)
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Set background colour
        glClearColor(0.97f, 0.79f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set uniform value before drawing occurs
        float currentTime = static_cast<float>(glfwGetTime());
        float redValue = (sin(currentTime) / 2.0f) + 0.5f;
        int colourUniformLocation = glGetUniformLocation(shaderProgram, "customColour");
        glUseProgram(shaderProgram);
        glUniform4f(colourUniformLocation, redValue, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

std::string loadShaderSource(const char* filename)
{
    std::ifstream file;
    std::stringstream buffer;

    std::string out = "";

    file.open(filename);

    if (file.is_open())
    {
        buffer << file.rdbuf();
        out = buffer.str();
    }

    else
    {
        std::cerr << "Could not open shader file: " << filename << std::endl;
    }

    file.close();

    return out;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


