/**
 * @file   bresenham.h
 * @brief  This file implements the Bresenham algorithm.
 */
#pragma once

#include <glad/glad.h>
#include <vector>

using uint = unsigned int;

/**
 * The Bresenham algorithm for rasterization
 */
namespace bresenham {

/**
 * @brief   Color represented in the form of RGB values
 */
struct color {
    GLubyte r = 0, g = 0, b = 0;

    auto operator==(const color &other) const -> bool {
        return r == other.r && g == other.g && b == other.b;
    }
};

/**
 * @brief   Screen
 */
class figure {
    uint m_width, m_height;
    std::vector<GLubyte> m_pixel_buffer;
    color m_rgb;
    auto get_pixel_color(uint x, uint y) -> color;

   public:
    figure(uint width, uint height);
    void set_color(color rgb);
    void add_pixel(uint x, uint y);
    void add_line(uint x1, uint y1, uint x2, uint y2);
    void add_circle(uint cx, uint cy, uint radius);
    void add_ellipse(uint cx, uint cy, uint a, uint b);
    void fill(uint ix, uint iy, color boundary_color);
    void draw();
};

}  // namespace bresenham