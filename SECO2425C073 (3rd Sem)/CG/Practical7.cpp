#include <GL/glut.h>
#include <cmath>

// Global variables for the sun's position and background color
float sunX = -0.8f;   // Starting X position of the sun
float sunY = -0.5f;   // Starting Y position of the sun
float skyR = 0.0f, skyG = 0.0f, skyB = 0.3f;  // Initial dark sky color (night)

// Function to draw a filled circle (sun)
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.9f, 0.0f);  // Yellow color for the sun
    glVertex2f(x, y);
    for (int angle = 0; angle <= 360; ++angle) {
        float theta = angle * 3.14159f / 180.0f;
        float cx = x + radius * cos(theta);
        float cy = y + radius * sin(theta);
        glVertex2f(cx, cy);
    }
    glEnd();
}

// Function to update the background color for day-night transition
void updateSkyColor() {
    if (sunY > 0.0f) {  // Daytime
        skyR = 0.53f;   // Light blue
        skyG = 0.81f;
        skyB = 0.92f;
    } else if (sunY > -0.5f) {  // Sunrise or Sunset
        skyR = 1.0f - (sunY + 0.5f);
        skyG = 0.5f - (sunY + 0.5f) / 2;
        skyB = 0.3f;
    } else {  // Nighttime
        skyR = 0.0f;
        skyG = 0.0f;
        skyB = 0.3f;
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set background color (sky)
    glClearColor(skyR, skyG, skyB, 1.0f);

    // Draw the sun
    drawCircle(sunX, sunY, 0.1f);

    glutSwapBuffers();
}

// Timer callback for animation
void timer(int) {
    // Update sun's position
    sunX += 0.01f;
    sunY = -0.5f + 0.6f * sin(sunX * 3.14159f);  // Arc-like motion

    // Reset sun's position when it goes out of view
    if (sunX > 1.0f) {
        sunX = -1.0f;
    }

    // Update sky color
    updateSkyColor();

    // Redisplay and set next timer
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sunrise and Sunset");

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Coordinate system

    glutMainLoop();
    return 0;
}
