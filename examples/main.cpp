#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<vector>

#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void makePixel(std::vector<GLubyte>& pixelBuffer, unsigned int x, unsigned int y) {
    int position = (x + y*WIDTH) * 3;
    pixelBuffer[position] = 255;
    pixelBuffer[position + 1] = 255;
    pixelBuffer[position + 2] = 255;
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

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::vector<GLubyte> pixelBuffer(WIDTH*HEIGHT*3);
        makePixel(pixelBuffer, 20, 30);
        glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());

        // GLint x = 200, y = 200;

        // glBegin(GL_POINTS);
        // glVertex2i(200, 200);
        // glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}