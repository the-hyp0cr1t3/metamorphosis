#include <bressenham/bressenham.h>

void Bressenham::Figure::addCircle(uint cx, uint cy, uint radius) {
    auto mirror8 = [this, cx, cy](int x, int y) {
        for (int sx : {-1, 1}) {
            for (int sy : {-1, 1}) {
                this->addPixel(sx * x + cx, sy * y + cy);
                this->addPixel(sy * y + cx, sx * x + cy);
            }
        }
    };

    uint x = 0, y = radius;
    int  d = 1 - radius, dE = 3, dSE = -2 * radius + 5;
    mirror8(x, y);

    while (y > x) {
        if (d < 0) {
            d += dE;
            dE += 2;
            dSE += 2;
        } else {
            d += dSE;
            dE += 2;
            dSE += 4;
            y--;
        }
        x++;
        mirror8(x, y);
    }
}