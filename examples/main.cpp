#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <bresenham/bresenham.h>

const int screen_width = 800, screen_height = 600;

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

auto main() -> int {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
      screen_width, screen_height, "DontLearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
      == 0) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    bresenham::figure figure(screen_width, screen_height);
    figure.set_color({255, 255, 255});
    figure.add_line(0, 100, 150, 0);  // -1 < m < 0: white
    figure.set_color({255, 0, 0});
    figure.add_line(0, 150, 150, 0);  // m = -1: red
    figure.set_color({0, 255, 0});
    figure.add_line(0, 200, 150, 0);  // -inf < m < -1: green
    figure.set_color({0, 0, 255});
    figure.add_line(600, 50, 600, 500);  // m = inf: blue
    figure.set_color({255, 255, 0});
    figure.add_line(300, 250, 800, 250);  // m = 0: yellow
    figure.set_color({0, 255, 255});
    figure.add_ellipse(400, 400, 100, 150);
    figure.set_color({255, 255, 0});
    figure.fill(400, 400, {0, 255, 255});

    while (glfwWindowShouldClose(window) == 0) {
        process_input(window);

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        figure.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}