#pragma once

#include <glad/glad.h>
#include <vector>

using uint = unsigned int;

namespace Bressenham {

struct Color {
    GLubyte r, g, b;
};

class Figure {
   private:
    uint width, height;
    std::vector<GLubyte> pixelBuffer;
    Color color;

   public:
    Figure(uint width, uint height);
    void setColor(Color color);
    void addPixel(uint x, uint y);
    void addLine(uint x1, uint y1, uint x2, uint y2);
    void addCircle(uint cx, uint cy, uint radius);
    void addEllipse(uint cx, uint cy, uint a, uint b);
    void draw();
};

}  // namespace Bressenham