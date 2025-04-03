#include <iostream>
#include <limits.h>
using namespace std;

#define SIZE 10 

class OBST {
    int p[SIZE]; // Success probabilities
    int a[SIZE]; // Sorted keys
    int w[SIZE][SIZE]; // Weights
    int c[SIZE][SIZE]; // Costs
    int r[SIZE][SIZE]; // Roots
    int n; // Number of keys

public:
    void get_data() {
        cout << "\nOptimal Binary Search Tree\n";
        cout << "\nEnter the number of nodes: ";
        cin >> n;

        cout << "\nEnter the keys (sorted):\n";
        for (int i = 1; i <= n; i++) {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }

        cout << "\nEnter the search probabilities (p[i]):\n";
        for (int i = 1; i <= n; i++) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }
    }

    int Min_Value(int i, int j) {
        int min_cost = INT_MAX;
        int k_best = i;

        for (int k = r[i][j - 1]; k <= r[i + 1][j]; k++) {
            int cost = c[i][k - 1] + c[k][j];
            if (cost < min_cost) {
                min_cost = cost;
                k_best = k;
            }
        }
        return k_best;
    }

    void build_OBST() {
        for (int i = 0; i <= n; i++) {
            w[i][i] = 0;
            c[i][i] = 0;
            r[i][i] = 0;
        }

        for (int i = 0; i < n; i++) {
            w[i][i + 1] = p[i + 1];
            c[i][i + 1] = p[i + 1];
            r[i][i + 1] = i + 1;
        }

        for (int m = 2; m <= n; m++) {
            for (int i = 0; i <= n - m; i++) {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j];

                int k = Min_Value(i, j);
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k;
            }
        }
    }

    void build_tree(int i, int j) {
        if (i >= j) return;

        int root = r[i][j];
        if (root == 0) return;

        cout << "\n\t" << a[root];

        if (root - 1 >= i && r[i][root - 1] != 0)
            cout << "\t\t" << a[r[i][root - 1]];
        else
            cout << "\t\t-";

        if (root + 1 <= j && r[root][j] != 0)
            cout << "\t" << a[r[root][j]];
        else
            cout << "\t-";

        build_tree(i, root - 1);
        build_tree(root, j);
    }

    void display_tree() {
        cout << "\nThe Optimal Binary Search Tree for the Given Nodes is:\n";
        cout << "The Root of this OBST is: " << a[r[0][n]] << endl;
        cout << "The Cost of this OBST is: " << c[0][n] << endl;
        cout << "\n\n\t NODE \t LEFT CHILD \t RIGHT CHILD\n";
        build_tree(0, n);
    }
};

int main() {
    OBST obj;
    obj.get_data();
    obj.build_OBST();
    obj.display_tree();
    return 0;
}
