#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

// Function to display adjacency list
void displayAdjList(vector<vector<int>>& adjList, vector<char>& vname){
    cout << "\nAdjacency List representation:\n";
    for (int i = 0; i < vname.size(); i++) {
        cout << vname[i] << " -> ";
        for (int neighbor : adjList[i]) {
            cout << vname[neighbor] << " ";
        }
        cout << endl;
    }
}

// BFS Traversal using adjacency list
void BFSTraversal(vector<vector<int>>& adjList, vector<char>& vname){
    int n = adjList.size();
    vector<bool> visited(n, false);
    queue<int> q;

    cout << "\nBFS Traversal: ";
    q.push(0);
    visited[0] = true;

    while(!q.empty()){
        int current = q.front();
        q.pop();
        cout << vname[current] << " ";

        for(int neighbor : adjList[current]){
            if(!visited[neighbor]){
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    cout << endl;
}

// DFS Traversal using adjacency matrix
void DFSTraversal(vector<vector<int>>& matrix, vector<char>& vname) {
    int n = matrix.size();
    vector<bool> visited(n, false);
    stack<int> s;

    cout << "\nDFS Traversal: ";
    s.push(0);
    visited[0] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << vname[current] << " ";

        for (int i = 0; i < n; i++) {
            if (matrix[current][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

int main(){
    int n;
    cout << "Enter Number of Landmarks: ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<vector<int>> adjList(n); // Separate adjacency list for BFS
    vector<char> vname;
    char vn;

    for(int i = 0; i < n; i++){
        cout << "\nEnter Name of Landmark " << i + 1 << ": ";
        cin >> vn;
        vname.push_back(vn);
    }

    int weight;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){ // Avoid duplicate edges & self-loops
            char inp;
            cout << "\nIs there a path between " << vname[i] << " and " << vname[j] << " (y/n): ";
            cin >> inp;
            if(inp == 'y'){
                cout << "Enter Distance of the Path: ";
                cin >> weight;
                matrix[i][j] = weight;
                matrix[j][i] = weight; // Since graph is undirected

                adjList[i].push_back(j); // Add to adjacency list
                adjList[j].push_back(i);
            }
        }
    }

    // Display adjacency matrix
    cout << "\nAdjacency Matrix Representation: \n   ";
    for(int i = 0; i < n; i++){
        cout << vname[i] << "  ";
    }
    cout << endl;
    
    for(int i = 0; i < n; i++){
        cout << vname[i] << "  ";
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << "  "; 
        }
        cout << endl;
    }

    displayAdjList(adjList, vname);
    BFSTraversal(adjList, vname);
    DFSTraversal(matrix, vname);

    return 0;
}
