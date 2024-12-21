#include <graphics.h>
#include <conio.h>
#include <cmath>

// Function to draw a line using DDA algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);
        x += xIncrement;
        y += yIncrement;
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
        delay(20);  // Visualization delay
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Rectangle coordinates
    int left = 150, top = 150, right = 350, bottom = 350;

    // Midpoints of rectangle sides (used for the diamond)
    int midTopX = (left + right) / 2, midTopY = top;          // Top mid
    int midRightX = right, midRightY = (top + bottom) / 2;    // Right mid
    int midBottomX = (left + right) / 2, midBottomY = bottom; // Bottom mid
    int midLeftX = left, midLeftY = (top + bottom) / 2;       // Left mid

    // Draw the rectangle
    drawLineDDA(left, top, right, top);       // Top side
    drawLineDDA(right, top, right, bottom);   // Right side
    drawLineDDA(right, bottom, left, bottom); // Bottom side
    drawLineDDA(left, bottom, left, top);     // Left side

    // Draw the diamond inside the rectangle
    drawLineDDA(midTopX, midTopY, midRightX, midRightY);     // Top to right
    drawLineDDA(midRightX, midRightY, midBottomX, midBottomY); // Right to bottom
    drawLineDDA(midBottomX, midBottomY, midLeftX, midLeftY); // Bottom to left
    drawLineDDA(midLeftX, midLeftY, midTopX, midTopY);       // Left to top

    // Draw the circle inscribed in the diamond
    int centerX = (left + right) / 2;         // Center X of diamond
    int centerY = (top + bottom) / 2;         // Center Y of diamond
    int radius = (right - left) / 2 / sqrt(2); // Radius of inscribed circle
    drawCircleBresenham(centerX, centerY, radius);

    getch();       // Wait for key press
    closegraph();  // Close graphics mode
    return 0;
}
