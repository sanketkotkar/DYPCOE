#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

typedef pair<int, int> pii;

void displayAdjMatrix(vector<vector<int>>& matrix, vector<string>& cityNames) {
    int n = cityNames.size();
    cout << "\nAdjacency Matrix Representation:\n    ";
    for (int i = 0; i < n; i++)
        cout << cityNames[i] << " ";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << cityNames[i] << " ";
        for (int j = 0; j < n; j++)
            cout << (matrix[i][j] == -1 ? 0 : matrix[i][j]) << "  ";
        cout << endl;
    }
}

void primMST(vector<vector<pii>>& adjList, vector<string>& cityNames, int n) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> minWeight(n, INT_MAX);
    int minCost = 0;

    pq.push({0, 0});
    minWeight[0] = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        minCost += weight;

        for (auto [w, v] : adjList[u]) {
            if (!visited[v] && w < minWeight[v]) {
                minWeight[v] = w;
                pq.push({w, v});
                parent[v] = u;
            }
        }
    }

    bool connected = true;
    for (bool v : visited)
        if (!v) connected = false;

    if (!connected) {
        cout << "\nThe graph is disconnected. MST cannot be formed!\n";
        return;
    }

    cout << "\nMinimum Spanning Tree (MST) using Prim's Algorithm:\n";
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1)
            cout << cityNames[parent[i]] << " - " << cityNames[i] << " with Weight: " << minWeight[i] << endl;
    }

    cout << "\nMinimum Cost using Prim's Algorithm: " << minCost << endl;
}

int main() {
    int n;
    cout << "Enter number of Cities: ";
    cin >> n;

    vector<string> cityNames(n);
    unordered_map<string, int> cityIndex;
    vector<vector<int>> adjMatrix(n, vector<int>(n, -1));
    vector<vector<pii>> adjList(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter name of City " << i + 1 << ": ";
        cin >> cityNames[i];
        cityIndex[cityNames[i]] = i;
    }

    char op;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Do you want a connection between " << cityNames[i] << " and " << cityNames[j] << "? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y') {
                int weight;
                cout << "Enter weight: ";
                cin >> weight;
                adjMatrix[i][j] = adjMatrix[j][i] = weight;
                adjList[i].push_back({weight, j});
                adjList[j].push_back({weight, i});
            }
        }
    }

    displayAdjMatrix(adjMatrix, cityNames);
    primMST(adjList, cityNames, n);

    return 0;
}
