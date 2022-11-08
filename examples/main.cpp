#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <bressenham/bressenham.h>

#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "DontLearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Bressenham::Figure figure(WIDTH, HEIGHT);
    figure.setColor({255, 255, 255});
    figure.addLine(0, 100, 150, 0); // -1 < m < 0: white
    figure.setColor({255, 0, 0});
    figure.addLine(0, 150, 150, 0); // m = -1: red
    figure.setColor({0, 255, 0});
    figure.addLine(0, 200, 150, 0); // -inf < m < -1: green
    figure.setColor({0, 0, 255});
    figure.addLine(600, 50, 600, 500); // m = inf: blue
    figure.setColor({255, 255, 0});
    figure.addLine(300, 250, 800, 250); // m = 0: yellow
    figure.setColor({0, 255, 255});
    figure.addEllipse(400, 400, 100, 150);
    figure.setColor({255, 255, 0});
    figure.fill(400, 400, {0, 255, 255});

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        figure.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}