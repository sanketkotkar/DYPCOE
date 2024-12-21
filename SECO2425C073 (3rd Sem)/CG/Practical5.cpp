#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

// Define a class for 2D points or objects
class Point {
private:
    float x, y;

public:
    // Constructor to initialize point
    Point(float x = 0, float y = 0) : x(x), y(y) {}

    // Method to display the point on the screen
    void draw(int centerX, int centerY) {
        putpixel(int(centerX + x), int(centerY - y), YELLOW);  // Draw point using putpixel
    }

    // Overload the + operator for Translation (translation by dx, dy)
    Point operator+(const Point& p) {
        return Point(x + p.x, y + p.y);
    }

    // Overload the * operator for Scaling (scaling by sx, sy)
    Point operator*(float scale) {
        return Point(x * scale, y * scale);
    }

    // Overload the * operator for Rotation (rotation by angle theta in radians)
    Point operator*(const float angle) {
        // Convert angle to radians
        float angleRad = angle * (M_PI / 180.0f);
        float cosTheta = cos(angleRad);
        float sinTheta = sin(angleRad);

        // Apply rotation matrix
        float newX = x * cosTheta - y * sinTheta;
        float newY = x * sinTheta + y * cosTheta;
        return Point(newX, newY);
    }

    // Getter methods for x and y
    float getX() { return x; }
    float getY() { return y; }
};

void drawShape(Point p1, Point p2, Point p3, Point p4, int centerX, int centerY) {
    // Draw the 2D shape (square or rectangle) by connecting the points
    line(centerX + p1.getX(), centerY - p1.getY(), centerX + p2.getX(), centerY - p2.getY());
    line(centerX + p2.getX(), centerY - p2.getY(), centerX + p3.getX(), centerY - p3.getY());
    line(centerX + p3.getX(), centerY - p3.getY(), centerX + p4.getX(), centerY - p4.getY());
    line(centerX + p4.getX(), centerY - p4.getY(), centerX + p1.getX(), centerY - p1.getY());
}

int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the center of the screen for transformations
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    // Define a 2D shape (square)
    Point p1(50, 50);  // First point of the square
    Point p2(50, -50); // Second point of the square
    Point p3(-50, -50); // Third point of the square
    Point p4(-50, 50);  // Fourth point of the square

    // Draw the original square
    drawShape(p1, p2, p3, p4, centerX, centerY);

    // Wait for a key press
    delay(2000);

    // Apply Scaling transformation (scale by 2)
    Point scaleFactor(2, 2);  // Scale by 2 for both x and y
    p1 = p1 * 2;
    p2 = p2 * 2;
    p3 = p3 * 2;
    p4 = p4 * 2;

    // Clear the screen and draw the scaled square
    cleardevice();
    drawShape(p1, p2, p3, p4, centerX, centerY);

    // Wait for a key press
    delay(2000);

    // Apply Translation transformation (translate by 100, 50)
    Point translation(100, 50);  // Translate by 100 on x-axis, 50 on y-axis
    p1 = p1 + translation;
    p2 = p2 + translation;
    p3 = p3 + translation;
    p4 = p4 + translation;

    // Clear the screen and draw the translated square
    cleardevice();
    drawShape(p1, p2, p3, p4, centerX, centerY);

    // Wait for a key press
    delay(2000);

    // Apply Rotation transformation (rotate by 45 degrees)
    float rotationAngle = 45.0f;  // Rotate by 45 degrees
    p1 = p1 * rotationAngle;
    p2 = p2 * rotationAngle;
    p3 = p3 * rotationAngle;
    p4 = p4 * rotationAngle;

    // Clear the screen and draw the rotated square
    cleardevice();
    drawShape(p1, p2, p3, p4, centerX, centerY);

    // Wait for a key press
    delay(2000);

    // Close the graphics window
    closegraph();
    return 0;
}
