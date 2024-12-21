#include <iostream>
#include <math.h>
#include <graphics.h>
#include <conio.h>
using namespace std;

class KochCurve {
public:
    void koch(int it, int x1, int y1, int x5, int y5) {
        int x2, y2, x3, y3, x4, y4, dx, dy;
        if (it == 0) {
            line(x1, y1, x5, y5);  // Draw line if recursion depth is 0
        }
        else {
            delay(50);  // Slow down the drawing process
            dx = (x5 - x1) / 3;
            dy = (y5 - y1) / 3;

            x2 = x1 + dx;
            y2 = y1 + dy;

            // Calculate the apex point of the equilateral triangle bump
            x3 = (int)(0.5 * (x1 + x5) + sqrt(3) * (y1 - y5) / 6);
            y3 = (int)(0.5 * (y1 + y5) + sqrt(3) * (x5 - x1) / 6);
            x4 = 2 * dx + x1;
            y4 = 2 * dy + y1;

            // Recursive call for the four new segments
            koch(it - 1, x1, y1, x2, y2);
            koch(it - 1, x2, y2, x3, y3);
            koch(it - 1, x3, y3, x4, y4);
            koch(it - 1, x4, y4, x5, y5);
        }
    }
};

int main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TurboC3\\BGI");  // Adjust path for your Turbo C++ BGI folder

    KochCurve k;
    k.koch(2, 150, 20, 20, 280);  // First side of the Koch curve
    k.koch(2, 20, 280, 280, 280);  // Second side of the Koch curve
    k.koch(2, 280, 280, 150, 20);  // Third side of the Koch curve

    getch();  // Wait for a key press
    closegraph();  // Close graphics mode
    return 0;
}
