#include <bresenham/bresenham.h>

void bresenham::figure::add_line(uint x1, uint y1, uint x2, uint y2) {
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = 2 * dy - dx;
    int d_e = 2 * dy;
    int d_ne = 2 * (dy - dx);
    int d_n = -2 * dx;
    int d_nw = -2 * (dy + dx);
    int d_w = -2 * dy;

    uint x = x1;
    uint y = y1;
    add_pixel(x, y);

    if (dx >= dy && dx >= 0) {  // 0 <= m <= 1
        while (x < x2) {
            if (d < 0) {
                d += d_e;
            } else {
                d += d_ne;
                y++;
            }
            x++;
            add_pixel(x, y);
        }
    } else if (dx < dy && dx >= 0) {  // 1 < m < inf

        while (y < y2) {
            if (d >= 0) {
                d += d_n;
            } else {
                d += d_ne;
                x++;
            }
            y++;
            add_pixel(x, y);
        }
    } else if (-dx < dy && dx < 0) {  // -inf < m < -1
        while (y < y2) {
            if (d < 0) {
                d += d_n;
            } else {
                d += d_nw;
                x--;
            }
            y++;
            add_pixel(x, y);
        }
    } else {  // -1 <= m < 0
        while (x > x2) {
            if (d >= 0) {
                d += d_w;
            } else {
                d += d_nw;
                y++;
            }
            x--;
            add_pixel(x, y);
        }
    }
}