#include <glad/glad.h>
#include <bressenham/bressenham.h>
#include <vector>

Bressenham::Figure::Figure(uint width, uint height)
  : pixelBuffer(width * height * 3), width(width), height(height) {}

void Bressenham::Figure::setColor(Color color) { this->color = color; }

void Bressenham::Figure::addPixel(uint x, uint y) {
    if (x >= width || y >= height) return;

    uint pos = (x + y * width) * 3;
    pixelBuffer[pos] = color.r;
    pixelBuffer[pos + 1] = color.g;
    pixelBuffer[pos + 2] = color.b;
}

// void Bressenham::Figure::addLine(uint x1, uint y1, uint x2, uint y2);
// void Bressenham::Figure::addRectangle(uint xmin, uint ymin, uint xmax, uint ymax);
// void Bressenham::Figure::addEllipse(uint cx, uint cy, uint a, uint b);

void Bressenham::Figure::draw() {
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());
}