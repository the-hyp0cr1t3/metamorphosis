/**
 * \file  bresenham.h
 * \brief Describes a struct to represent color, a class to represent a Figure in a namespace called bresenham
 */
#pragma once

#include <glad/glad.h>
#include <vector>
#include <fstream>

/// For the sake of brevity.
using uint = unsigned int;

/// The Bresenham midpoint algorithm for rasterization.
namespace bresenham {

/**
 * \brief  The RGB codes to represent colors.
 *
 * The RGB color model consists of three additive primary colors,
 * red, green, and blue. They can be added together in various ways
 * to reproduce a broad array of colors.
 *
 * Each parameter (red, green, and blue) defines the intensity
 * of its color as an integer between 0 and 255.
 *
 * For example, RGB(0, 0, 255) is rendered as blue,
 * because the blue parameter is set to its highest value (255)
 * and the others are set to 0.
 */
struct color {
    GLubyte r = 0;  ///< The red parameter.
    GLubyte g = 0;  ///< The green parameter.
    GLubyte b = 0;  ///< The blue parameter.

    /// An equals overload to compare color objects.
    auto operator==(const color &other) const -> bool {
        return r == other.r && g == other.g && b == other.b;
    }
};

/**
 * \brief Manage pixel-by-pixel writes to the frame buffer.
 * 
 * It stores and manages the pixel buffer to be rendered to the screen.
 * The RGB codes of individual pixels' can be set to produce visual elements.
 *
 * The class provides the following primitive drawing methods:
 *  - add_pixel()
 *  - add_line()
 *  - add_circle()
 *  - add_ellipse()
 *
 * The color to be used by the `add_*()` primitives can be
 * set by set_color(), prior to the function calls.
 *
 * Finally, the block of pixels can be added
 * to the frame buffer by calling draw().
 */
class figure {
   public:
    /**
     * \brief Constructor.
     * 
     * \param width The width of the screen in pixels.
     * \param height The height of the screen in pixels.
     */
    figure(uint width, uint height);

    /**
     * \brief Sets the pixel drawing color `m_rgb`.
     *
     * Any `add_*()` commands will use the currently set `m_rgb` value.
     * 
     * \param rgb The color to set.
     */
    void set_color(color rgb);

    /**
     * \brief Draws a single pixel.
     *
     * Uses the currently set `m_rgb` value.
     * 
     * \param x The \f$x\f$ coordinate of the pixel. \f$(0 \le x \lt width)\f$
     * \param y The \f$y\f$ coordinate of the pixel. \f$(0 \le y \lt height)\f$
     */
    void add_pixel(uint x, uint y);

    /**
     * \brief Draws a straight line between two given pixels
     * using the Bresenham midpoint algorithm.
     * 
     * Uses the currently set `m_rgb` value.
     *
     * \param x1 The \f$x\f$ coordinate of the first pixel. \f$(0 \le x_1 \lt width)\f$
     * \param y1 The \f$y\f$ coordinate of the first pixel. \f$(0 \le y_1 \lt height)\f$
     * \param x2 The \f$x\f$ coordinate of the second pixel. \f$(0 \le x_2 \lt width)\f$
     * \param y2 The \f$y\f$ coordinate of the second pixel. \f$(0 \le y_2 \lt height)\f$
     */
    void add_line(uint x1, uint y1, uint x2, uint y2);

    /**
     * \brief Draws a circle using the midpoint algorithm.
     *
     * Uses the currently set `m_rgb` value.
     *
     * \param cx The \f$x\f$ coordinate of the center of the circle. \f$(0 \le c_x \lt width)\f$
     * \param cy The \f$y\f$ coordinate of the center of the circle. \f$(0 \le c_y \lt height)\f$
     * \param radius The radius of the circle in pixels.
     */
    void add_circle(uint cx, uint cy, uint radius);

    /**
     * \brief Draws an axes-aligned ellipse using the midpoint algorithm.
     * 
     * Uses the currently set `m_rgb` value.
     *
     * \param cx The \f$x\f$ coordinate of the center of the ellipse. \f$(0 \le c_x \lt width)\f$
     * \param cy The \f$y\f$ coordinate of the center of the ellipse. \f$(0 \le c_y \lt height)\f$
     * \param a The length of the horizontal axis in pixels.
     * \param b The length of the vertical axis in pixels
     */
    void add_ellipse(uint cx, uint cy, uint a, uint b);

    /**
     * \brief Fills a bounded region using the Boundary Fill algorithm.
     *
     * Uses the currently set `m_rgb` value as the fill color.
     *
     * Starts at the given pixel and recursively colors adjacent pixels
     * until a pixel of color boundary_color is found or the end of the
     * screen is reached.
     *
     * Only a single boundary color is supported.
     * 
     * \param x The \f$x\f$ coordinate of an interior point in the region. \f$(0 \le x \lt width)\f$
     * \param y The \f$y\f$ coordinate of an interior point in the region. \f$(0 \le y \lt height)\f$
     * \param boundary_color The color of the boundary pixels.
     */
    void fill(uint x, uint y, color boundary_color);

    /**
     * \brief Writes the block of pixels to the frame buffer.
     * 
     * Is usually preceeded by one or more `add_*()` commands.
     */
    void draw();

   private:
    /// An internal function to get the color of a pixel at given coordinates
    auto get_pixel_color(uint x, uint y) -> color;

   protected:
    uint m_width;  ///< The width of the screen in pixels.
    uint m_height;  ///< The height of the screen in pixels.

    /// A pixel buffer which stores the pixel colors.
    std::vector<GLubyte> m_pixel_buffer;

    // The color to be used by the `add_*()` primitives.
    color m_rgb;
};

}  // namespace bresenham

std::istream &operator>>(std::istream &is, bresenham::figure &fig);