#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGLFinally", NULL, NULL);
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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.05f, -0.05f, 0.0f,
        0.0f, 0.5f, 0.0f};

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering
        green += 0.01f;
        if (green > 1.0f)
            green = 0.0f;

        glClearColor(0.2f, green, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
