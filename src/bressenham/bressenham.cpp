#include <glad/glad.h>
#include <bressenham/bressenham.h>
#include <vector>
#include <iostream>

Bressenham::Figure::Figure(uint width, uint height)
  : pixelBuffer(width * height * 3), width(width), height(height) {}

void Bressenham::Figure::setColor(Color color) { this->color = color; }

Bressenham::Color Bressenham::Figure::getPixelColor(uint x, uint y) {
    uint pos = (x + y * width) * 3;
    return {pixelBuffer[pos], pixelBuffer[pos + 1], pixelBuffer[pos + 2]};
}

void Bressenham::Figure::addPixel(uint x, uint y) {
    if (x >= width || y >= height) return;

    uint pos = (x + y * width) * 3;
    pixelBuffer[pos] = color.r;
    pixelBuffer[pos + 1] = color.g;
    pixelBuffer[pos + 2] = color.b;
}

void Bressenham::Figure::fill(uint ix, uint iy, Color boundaryColor) {
    if (ix >= width || iy >= height
      || color == getPixelColor(ix, iy)
      || boundaryColor == getPixelColor(ix, iy))
        return;

    addPixel(ix, iy);

    fill(ix - 1, iy, boundaryColor);
    fill(ix + 1, iy, boundaryColor);
    fill(ix, iy - 1, boundaryColor);
    fill(ix, iy + 1, boundaryColor);
}

void Bressenham::Figure::draw() {
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());
}