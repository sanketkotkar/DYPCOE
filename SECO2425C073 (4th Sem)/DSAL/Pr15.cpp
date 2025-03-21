#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

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
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-Heap
    vector<bool> visited(n, false);
    int minCost = 0;

    pq.push({0, 0}); // Start from node 0

    cout << "\nMinimum Spanning Tree (MST) Edges:\n";
    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (visited[u]) continue; // Ignore visited nodes

        visited[u] = true;
        minCost += weight;
        if (u != 0) // Skip the first node as it has no parent
            cout << cityNames[u] << " with Weight: " << weight << endl;

        for (auto [w, v] : adjList[u]) {
            if (!visited[v])
                pq.push({w, v});
        }
    }

    cout << "\nMinimum Cost: " << minCost << endl;
}

int main() {
    int n;
    cout << "Enter number of Cities: ";
    cin >> n;

    vector<string> cityNames(n);
    unordered_map<string, int> cityIndex;
    vector<vector<int>> adjMatrix(n, vector<int>(n, -1));
    vector<vector<pii>> adjList(n);

    // Input city names
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
