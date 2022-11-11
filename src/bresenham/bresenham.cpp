#include <glad/glad.h>
#include <bresenham/bresenham.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

bresenham::figure::figure(uint width, uint height)
  : m_width(width), m_height(height), m_pixel_buffer(width * height * 3, 255) {}

void bresenham::figure::set_color(color rgb) { m_rgb = rgb; }

auto bresenham::figure::get_pixel_color(uint x, uint y) -> bresenham::color {
    uint pos = (x + y * m_width) * 3;
    return {
      m_pixel_buffer[pos], m_pixel_buffer[pos + 1], m_pixel_buffer[pos + 2]};
}

void bresenham::figure::add_pixel(uint x, uint y) {
    if (x >= m_width || y >= m_height) return;

    uint pos = (x + y * m_width) * 3;
    m_pixel_buffer[pos] = m_rgb.r;
    m_pixel_buffer[pos + 1] = m_rgb.g;
    m_pixel_buffer[pos + 2] = m_rgb.b;
}

void bresenham::figure::fill(uint ix, uint iy, color boundary_color) {
    if (ix >= m_width || iy >= m_height || m_rgb == get_pixel_color(ix, iy)
      || boundary_color == get_pixel_color(ix, iy))
        return;

    add_pixel(ix, iy);

    fill(ix - 1, iy, boundary_color);
    fill(ix + 1, iy, boundary_color);
    fill(ix, iy - 1, boundary_color);
    fill(ix, iy + 1, boundary_color);
}

void bresenham::figure::draw() {
    glDrawPixels(
      m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_pixel_buffer.data());
}

std::istream &bresenham::operator>>(std::istream &in, bresenham::figure &fig) {
    in.exceptions(std::istream::badbit);

    std::string command;
    while (std::getline(in, command)) {
        std::cout << "======================" << std::endl;
        std::cout << command << std::endl;
        std::stringstream ss(command);
        std::string op;
        ss >> op;
        if (op == "sc") {
            bresenham::color col;
            ss >> col.r >> col.g >> col.b;
            fig.set_color(col);
        } else if (op == "al") {
            uint x1, y1, x2, y2;
            ss >> x1 >> y1 >> x2 >> y2;
            y1 = 900 - y1, y2 = 900 - y2;
            fig.add_line(x1, y1, x2, y2);
        } else if (op == "ac") {
            uint cx, cy, radius;
            ss >> cx >> cy >> radius;
            cy = 900 - cy;
            fig.add_circle(cx, cy, radius);
        } else if (op == "ae") {
            uint cx, cy, a, b;
            ss >> cx >> cy >> a >> b;
            cy = 900 - cy;
            fig.add_ellipse(cx, cy, a, b);
        } else if (op == "fill") {
            uint x, y;
            bresenham::color col;
            ss >> x >> y >> col.r >> col.g >> col.b;
            fig.fill(x, y, col);
        } else {
            continue;
        }
    }
    std::cout << "Finished reading file" << std::endl;

    return in;
}
