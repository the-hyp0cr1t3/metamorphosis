#include <bresenham/bresenham.h>

void bresenham::figure::add_circle(uint cx, uint cy, uint radius) {
    auto mirror8 = [this, cx, cy](int x, int y) {
        for (int sx : {-1, 1}) {
            for (int sy : {-1, 1}) {
                this->add_pixel(sx * x + cx, sy * y + cy);
                this->add_pixel(sy * y + cx, sx * x + cy);
            }
        }
    };

    uint x = 0;
    uint y = radius;
    int d = 1 - radius;
    int d_e = 3;
    int d_se = -2 * radius + 5;
    mirror8(x, y);

    while (y > x) {
        if (d < 0) {
            d += d_e;
            d_e += 2;
            d_se += 2;
        } else {
            d += d_se;
            d_e += 2;
            d_se += 4;
            y--;
        }
        x++;
        mirror8(x, y);
    }
}