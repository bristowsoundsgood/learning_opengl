
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(0.09f, 0.0f, 0.25f, 1.0f);\n"
                                   "}\0";

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

    // Compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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

    // Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed." << '\n' << infoLog << std::endl;
        return -1;
    }

    // Create shader program
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
    constexpr float triangleA[] = {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    constexpr float triangleB[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    // ==== loading triangle data into OpenGL ===
    unsigned int VAOs[2];
    unsigned int VBOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (triangleA), triangleA, GL_STATIC_DRAW);

    glBindVertexArray(VAOs[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (triangleB), triangleB, GL_STATIC_DRAW);

    glBindVertexArray(VAOs[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Rendering loop.
    // This is where all rendering commands are executed (i.e., calculating pixel colours)
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Set background colour
        glClearColor(0.97f, 0.79f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

