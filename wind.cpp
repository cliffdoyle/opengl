#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

std::string readShaderFile(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to openfile" << '\n';
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "LearnOpenGLFinally", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << "\n";
        return -1;
    }
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    glViewport(0, 0, fbWidth, fbHeight);

    float green = 0.0f;

    GLuint vbo;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::cout << "buffer: " << vbo << '\n';

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Compiling the shaders
    std::string vertexShaderSource = readShaderFile("triangle.vert");
    std::string fragshadersource = readShaderFile("triangle.frag");
    const char *vertexCode = vertexShaderSource.c_str();
    const char *fragCode = fragshadersource.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    // Fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragCode, NULL);
    glCompileShader(fragmentShader);

    // Error handling in shadercompilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << '\n';
    }

    // error handling in fragment shader
    int success2;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
    if (!success2)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << '\n';
    }

    // linking shaders to the program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); // shader program is the finasl linked version of multiple shaders combined
    // glCreateProgram function creates a program and returns the ID reference
    // to the newly created program object.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Delete shader objects once linked into the program object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // check linking errors
    int success3;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << '\n';
    }

    // Linking Vertex Attributes
    // specifying how OpenGl should interpret the vertex data be4 rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering
        green += 0.01f;
        if (green > 1.0f)
        green = 0.0f;
        glClearColor(0.2f, green, 0.3f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT);
        // use shader program to render
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
