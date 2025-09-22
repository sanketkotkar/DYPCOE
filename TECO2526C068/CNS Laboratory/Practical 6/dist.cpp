#include <iostream>
#include <vector>
using namespace std;

#define INF 9999
#define MAX 20

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    int dist[MAX][MAX];
    int nextHop[MAX][MAX];

    cout << "Enter costs:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                nextHop[i][j] = i;
            } else {
                cout << "Cost from " << i << " to " << j << " (9999 if no direct path): ";
                cin >> dist[i][j];
                nextHop[i][j] = (dist[i][j] != INF) ? j : -1;
            }
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }

    auto printPath = [&](int i, int j) {
        if (nextHop[i][j] == -1) {
            cout << "No path";
            return;
        }
        cout << i;
        while (i != j) {
            i = nextHop[i][j];
            cout << " -> " << i;
        }
    };

    cout << "\nShortest paths and costs:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "From " << i << " to " << j << ": ";
                if (dist[i][j] == INF) {
                    cout << "No path\n";
                } else {
                    printPath(i, j);
                    cout << " | Cost: " << dist[i][j] << "\n";
                }
            }
        }
    }

    return 0;
}

