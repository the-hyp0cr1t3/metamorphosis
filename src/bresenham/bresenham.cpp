#include <glad/glad.h>
#include <bresenham/bresenham.h>
#include <vector>
#include <iostream>

bresenham::figure::figure(uint width, uint height)
  : m_width(width), m_height(height), m_pixel_buffer(width * height * 3) {}

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