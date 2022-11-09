#include <bresenham/bresenham.h>

void bresenham::figure::add_ellipse(uint cx, uint cy, uint a, uint b) {
    auto mirror4 = [this, cx, cy](int x, int y) {
        for (int sx : {-1, 1})
            for (int sy : {-1, 1}) this->add_pixel(sx * x + cx, sy * y + cy);
    };

    int x = 0;
    int y = b;
    int a2 = a * a;
    int b2 = b * b;
    mirror4(x, y);

    int d1 = 4 * b2 + a2 * (-4 * b + 1);
    while (a2 * (2 * y - 1) > 2 * b2 * (x + 1)) {
        if (d1 < 0) {
            d1 += 4 * b2 * (2 * x + 3);
        } else {
            d1 += 4 * b2 * (2 * x + 3) + 4 * a2 * (-2 * y + 2);
            y--;
        }
        x++;
        mirror4(x, y);
    }

    int d2 =
      b2 * (2 * x + 1) * (2 * x + 1) + 4 * a2 * (y - 1) * (y - 1) - 4 * a2 * b2;
    while (y > 0) {
        if (d2 >= 0) {
            d2 += 4 * a2 * (-2 * y + 3);
        } else {
            d2 += 4 * b2 * (2 * x + 2) + 4 * a2 * (-2 * y + 3);
            x++;
        }
        y--;
        mirror4(x, y);
    }
}