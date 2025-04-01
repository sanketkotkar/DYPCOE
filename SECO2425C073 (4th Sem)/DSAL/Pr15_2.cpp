#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge {
    int u, v, weight;
};

class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void kruskalMST(vector<Edge>& edges, vector<string>& cityNames, int n) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DisjointSet ds(n);
    vector<Edge> mst;
    int minCost = 0;

    cout << "\nApplying Kruskal's Algorithm...\n";

    for (Edge e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            ds.unite(e.u, e.v);
            mst.push_back(e);
            minCost += e.weight;
        }
        if (mst.size() == n - 1) break;
    }

    if (mst.size() != n - 1) {
        cout << "\nThe graph is disconnected. MST cannot be formed!\n";
        return;
    }

    cout << "\nMinimum Spanning Tree (MST) using Kruskal's Algorithm:\n";
    for (Edge e : mst) {
        cout << cityNames[e.u] << " - " << cityNames[e.v] << " with Weight: " << e.weight << endl;
    }
    cout << "\nMinimum Cost using Kruskal's Algorithm: " << minCost << endl;
}

int main() {
    int n;
    cout << "Enter number of Cities: ";
    cin >> n;

    vector<string> cityNames(n);
    unordered_map<string, int> cityIndex;
    vector<Edge> edges;

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
                edges.push_back({i, j, weight});
            }
        }
    }

    kruskalMST(edges, cityNames, n);

    return 0;
}
