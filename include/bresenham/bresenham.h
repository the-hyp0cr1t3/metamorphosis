/**
 * \file bresenham.h
 * \brief Describes a struct to represent color, a class to represent a Figure in a namespace called bresenham
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <glad/glad.h>
#include <vector>

using uint = unsigned int;

/*!
 * \namespace bresenham
 *
 * The Bresenham midpoint algorithms for rasterization
 */
namespace bresenham {

/**
 * \struct color
 *
 * \brief   Color represented in the form of RGB values
 */
struct color {
    GLubyte r = 0, g = 0, b = 0;

    auto operator==(const color &other) const -> bool {
        return r == other.r && g == other.g && b == other.b;
    }
};

/*!
 * \class figure
 *
 * \brief The Figure class represents the figure that will be displayed. Different primitives can be drawn (added to the figure) and rendered.
 * 
 */
class figure {
    uint m_width, m_height;

    // A vector of integers which stores ith pixels' RGB color in i, i+1 and i+2 respectively
    std::vector<GLubyte> m_pixel_buffer;

    // The current color. This is the color that is used to draw primitives
    color m_rgb;

    // An internal function to get the color of the pixel at given coordinates
    auto get_pixel_color(uint x, uint y) -> color;

   public:

    /**
     * \brief Construct a new empty figure object
     * 
     * \param width The width of the figure in pixels
     * \param height The height of the figure in pixels
     */
    figure(uint width, uint height);

    /**
     * \brief Set the current color (The color used to dra primitives)
     * 
     * \param rgb The color
     */
    void set_color(color rgb);

    /**
     * \brief Draws a single pixel
     * 
     * \param x The X coordinate of the pixel (0 <= x < width)
     * \param y The Y coordinate of the pixel (0 <= y < height)
     */
    void add_pixel(uint x, uint y);

    /**
     * \brief Given two pixels, draws a straight line between the two pixels using the Bressenham midpoint algorithm
     * 
     * \param x1 The X coordinate of the first pixel (0 <= x < width)
     * \param y1 The Y coordinate of the first pixel (0 <= y < height)
     * \param x2 The X coordinate of the second pixel (0 <= x < width)
     * \param y2 The Y coordinate of the second pixel (0 <= y < height)
     */
    void add_line(uint x1, uint y1, uint x2, uint y2);

    /**
     * \brief Draws a circle using the midpoint algorithm
     * 
     * \param cx The X coordinate of the center of the circle (0 <= cx < width)
     * \param cy The Y coordinate of the center of the circle (0 <= cy < height)
     * \param radius The radius of the circle in pixels
     */
    void add_circle(uint cx, uint cy, uint radius);

    /**
     * \brief Drawn an axes aligned ellipse using the midpoint algorithm
     * 
     * \param cx The X coordinate of the center of the ellipse (0 <= cx < width)
     * \param cy The Y coordinate of the center of the ellipse (0 <= cy < height)
     * \param a The length of the horizontal axis in pixels
     * \param b The length of the vertical axis in pixels
     */
    void add_ellipse(uint cx, uint cy, uint a, uint b);

    /**
     * \brief Fills a bounded region using the current color using the Boundary Fill algorithm
     * 
     * \param ix The X coordinate of an interior point in the region (0 <= ix < width)
     * \param iy The Y coordinate of an interior point in the region (0 <= iy < height)
     * \param boundary_color The color of the boundary
     */
    void fill(uint ix, uint iy, color boundary_color);

    /**
     * \brief Renders the current figure with all the primitives in the object
     * 
     */
    void draw();
};

}  // namespace bresenham