#include <glad/glad.h>
#include <bresenham/bresenham.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

bresenham::figure::figure(uint width, uint height)
  : m_width(width), m_height(height), m_pixel_buffer(width * height * 3, 255) {}

void bresenham::figure::flip_vertically(bool flip) { m_flip = flip; }

void bresenham::figure::set_color(color rgb) { m_rgb = rgb; }

auto bresenham::figure::get_pixel_color(uint x, uint y) -> bresenham::color {
    uint pos = (x + y * m_width) * 3;
    return {
      m_pixel_buffer[pos], m_pixel_buffer[pos + 1], m_pixel_buffer[pos + 2]};
}

void bresenham::figure::add_pixel(uint x, uint y) {
    if (x >= m_width || y >= m_height) return;

    if (m_flip) y = m_height - y - 1;

    uint pos = (x + y * m_width) * 3;
    m_pixel_buffer[pos] = m_rgb.r;
    m_pixel_buffer[pos + 1] = m_rgb.g;
    m_pixel_buffer[pos + 2] = m_rgb.b;
}

void bresenham::figure::fill(uint ix, uint iy, color boundary_color) {
    if (m_flip) {
        if (ix >= m_width || iy >= m_height
          || m_rgb == get_pixel_color(ix, m_height - iy - 1)
          || boundary_color == get_pixel_color(ix, m_height - iy - 1))
            return;
    } else {
        if (ix >= m_width || iy >= m_height || m_rgb == get_pixel_color(ix, iy)
          || boundary_color == get_pixel_color(ix, iy))
            return;
    }

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

std::istream &operator>>(std::istream &in, bresenham::figure &fig) {
    in.exceptions(std::istream::badbit);

    std::string command;
    while (std::getline(in, command)) {
        std::stringstream ss(command);
        std::string op;
        ss >> op;
        if (op == "sc") {
            uint r, g, b;
            ss >> r >> g >> b;
            fig.set_color({r, g, b});
        } else if (op == "al") {
            uint x1, y1, x2, y2;
            ss >> x1 >> y1 >> x2 >> y2;
            fig.add_line(x1, y1, x2, y2);
        } else if (op == "ac") {
            uint cx, cy, radius;
            ss >> cx >> cy >> radius;
            fig.add_circle(cx, cy, radius);
        } else if (op == "ae") {
            uint cx, cy, a, b;
            ss >> cx >> cy >> a >> b;
            fig.add_ellipse(cx, cy, a, b);
        } else if (op == "fill") {
            uint x, y;
            uint r, g, b;
            ss >> x >> y >> r >> g >> b;
            fig.fill(x, y, {r, g, b});
        } else {
            continue;
        }
    }

    return in;
}
