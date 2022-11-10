#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <bresenham/bresenham.h>

const int screen_width = 1600, screen_height = 900;

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void render_frame(std::string file_name, bresenham::figure &figure) { 
    std::ifstream ifs = std::ifstream(file_name, std::ios_base::in);
    ifs.open(file_name);
    if (!ifs.is_open()) { 
        std::cerr << "File could not be opened\n";
        return;
    }

    std::string command;
    while (std::getline(ifs, command)) {
        std::istringstream iss(command);
        std::string operation;
        iss >> operation;
        if (operation == "al") {
            int x1, y1, x2, y2;
            iss >> x1 >> y1 >> x2 >> y2;
            y1 = 900 - y1, y2 = 900 - y2;
            figure.add_line(x1, y1, x2, y2);
        } else if (operation == "ac") {
            int cx, cy, radius;
            iss >> cx >> cy >> radius;
            cy = 900 - cy;
            figure.add_circle(cx, cy, radius);
        } else if (operation == "ae") {
            int cx, cy, a, b;
            iss >> cx >> cy >> a >> b;
            cy = 900 - cy;
            figure.add_ellipse(cx, cy, a, b);
        } else {
            continue;
        }
    }
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
    figure.set_color({0, 0, 0});
    render_frame("frames/frame-1.txt", figure);
    //figure.add_line(0, 100, 150, 0);  // -1 < m < 0: white
    //figure.set_color({255, 0, 0});
    //figure.add_line(0, 150, 150, 0);  // m = -1: red
    //figure.set_color({0, 255, 0});
    //figure.add_line(0, 200, 150, 0);  // -inf < m < -1: green
    //figure.set_color({0, 0, 255});
    //figure.add_line(600, 50, 600, 500);  // m = inf: blue
    //figure.set_color({255, 255, 0});
    //figure.add_line(300, 250, 800, 250);  // m = 0: yellow
    //figure.set_color({0, 255, 255});
    //figure.add_ellipse(400, 400, 100, 150);
    //figure.set_color({255, 255, 0});
    //figure.fill(400, 400, {0, 255, 255});

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