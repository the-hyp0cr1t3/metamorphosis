#include <bressenham/bressenham.h>
#include<iostream>

void Bressenham::Figure::addLine(uint x1, uint y1, uint x2, uint y2) {
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1, dy = y2 - y1;
    int d = 2 * dy - dx;
    int dE = 2 * dy, dNE = 2 * (dy - dx), dN = -2 * dx, dNW = -2 * (dy + dx), dW = -2 * dy;

    int x = x1, y = y1;
    addPixel(x, y);

    if (dx >= dy && dx >= 0) {  // 0 <= m <= 1
        while (x < x2) {
            if (d < 0) d += dE;
            else {
                d += dNE;
                y++;
            }
            x++;
            addPixel(x, y);
        }
    } else if (dx < dy && dx >= 0) {  // 1 < m < inf

        while (y < y2) {
            if (d >= 0) d += dN;
            else {
                d += dNE;
                x++;
            }
            y++;
            addPixel(x, y);
        }
    } else if (-dx < dy && dx < 0) {  // -inf < m < -1
        while (y < y2) {
            if (d < 0) d += dN;
            else {
                d += dNW;
                x--;
            }
            y++;
            addPixel(x, y);
        }
    } else {  // -1 <= m < 0
        while (x > x2) {
            if (d >= 0) d += dW;
            else {
                d += dNW;
                y++;
            }
            x--;
            addPixel(x, y);
        }
    }
}