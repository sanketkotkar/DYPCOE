//Write C++ program to draw a concave polygon and fill it with desired color using scan fill algorithm. Apply the concept of inheritance.
#include <graphics.h>
#include <iostream>
#include <algorithm>

using namespace std;

// Base class for polygons
class Polygon {
protected:
    int x[10], y[10];  // Coordinates of the polygon vertices (up to 10 vertices)
    int edges;  // Number of edges in the polygon
public:
    // Constructor to initialize the polygon
    Polygon(int vertices_x[], int vertices_y[], int num_edges) {
        for (int i = 0; i < num_edges; i++) {
            x[i] = vertices_x[i];
            y[i] = vertices_y[i];
        }
        edges = num_edges;
    }
    virtual void scanFill() = 0;  // Pure virtual function for scan filling
};

// Derived class for ConcavePolygon
class ConcavePolygon : public Polygon {
public:
    ConcavePolygon(int vertices_x[], int vertices_y[], int num_edges) : Polygon(vertices_x, vertices_y, num_edges) {}

    void scanFill() override {
        int i, j, temp;
        int xmin = getmaxx(), xmax = 0;

        // Find the minimum and maximum x-coordinates of the polygon
        for (i = 0; i < edges; i++) {
            if (x[i] < xmin) xmin = x[i];
            if (x[i] > xmax) xmax = x[i];
        }

        // Scan each scan-line within the polygon's vertical extent
        for (i = xmin; i <= xmax; i++) {
            // Initialize an array to store the intersection points
            int interPoints[10];  // Can store up to 10 intersection points
            int count = 0;

            for (j = 0; j < edges; j++) {
                int next = (j + 1) % edges;

                // Check if the current edge intersects with the scan line
                if ((y[j] > i && y[next] <= i) || (y[next] > i && y[j] <= i)) {
                    interPoints[count++] = x[j] + (i - y[j]) * (x[next] - x[j]) / (y[next] - y[j]);
                }
            }

            // Sort the intersection points in ascending order
            for (j = 0; j < count - 1; j++) {
                for (int k = 0; k < count - j - 1; k++) {
                    if (interPoints[k] > interPoints[k + 1]) {
                        temp = interPoints[k];
                        interPoints[k] = interPoints[k + 1];
                        interPoints[k + 1] = temp;
                    }
                }
            }

            // Set the fill color (e.g., light blue)
            setfillstyle(SOLID_FILL, LIGHTBLUE);  // You can change LIGHTBLUE to any color you like

            // Fill the pixels between pairs of intersection points
            for (j = 0; j < count; j += 2) {
                // Use flood fill between pairs of intersection points
                floodfill((interPoints[j] + interPoints[j + 1]) / 2, i, WHITE);  // The center of the polygon
            }
        }
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Define a concave polygon (example: a simple concave shape with 5 points)
    int x[] = {100, 200, 300, 250, 150};
    int y[] = {100, 100, 200, 300, 250};
    int edges = 5;

    // Create a ConcavePolygon object
    ConcavePolygon concave(x, y, edges);

    // Fill the concave polygon using scan fill
    concave.scanFill();

    delay(5000);
    closegraph();
    return 0;
}

