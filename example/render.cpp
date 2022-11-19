#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include <bresenham/bresenham.h>

const int screen_width = 1600, screen_height = 900;

// executes whenever the window size changed (by OS or user resize)
void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

// query glfw for key presses / mouse movements in the current frame
void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

auto main(int argc, char **argv) -> int {
    if (argc == 1) {
        std::cerr << "Usage: ./render [file]" << std::endl;
        return 1;
    }

    std::string file = argv[1];
    std::ifstream file_in(file);

    if (!file_in.is_open())
        throw std::iostream::failure("Could not open " + file);

    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // glfw: create window
    GLFWwindow *window = glfwCreateWindow(
      screen_width, screen_height, "Metamorphosis", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load OpenGL function pointers
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
      == 0) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    bresenham::figure fig(screen_width, screen_height);
    fig.flip_vertically(true);
    file_in >> fig;

    // render loop
    while (glfwWindowShouldClose(window) == 0) {
        process_input(window);

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        fig.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: deallocate GLFW resources.
    glfwTerminate();
}