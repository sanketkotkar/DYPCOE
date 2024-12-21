#include <graphics.h>
#include <conio.h>
#include <cmath>

// Function to draw a line using the DDA algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));  // Determine the number of steps
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);  // Plot the pixel
        x += xIncrement;  // Increment the x coordinate
        y += yIncrement;  // Increment the y coordinate
    }
}

// Function to plot 8 symmetric points for Bresenham's Circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

// Function to draw a circle using Bresenham's algorithm
void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        delay(50);  // Visualization delay
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Draw the triangle using DDA algorithm
    drawLineDDA(200, 200, 100, 400);  // Left side of triangle
    drawLineDDA(100, 400, 300, 400);  // Base of triangle
    drawLineDDA(300, 400, 200, 200);  // Right side of triangle

    // Draw circles using Bresenham's algorithm
    drawCircleBresenham(200, 326, 128);  // Outer circle
    drawCircleBresenham(200, 338, 60);   // Inner circle

    getch();       // Wait for key press
    closegraph();  // Close graphics mode
    return 0;
}
