#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Graph {
    int V;
    bool isDirected;
    unordered_map<int, vector<int>> adj;

public:
    Graph(int vertices, bool directed = false) {
        V = vertices;
        isDirected = directed;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!isDirected)
            adj[v].push_back(u);
    }

    void printGraph() {
        cout << "\nGraph Adjacency List:\n";
        for (auto& p : adj) {
            cout << p.first << ": ";
            for (auto& x : p.second) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    bool isCyclicUndirectedUtil(int node, int parent, vector<bool>& visited) {
        visited[node] = true;

        for (auto& neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (isCyclicUndirectedUtil(neighbor, node, visited))
                    return true;
            } else if (neighbor != parent) {
                return true;
            }
        }

        return false;
    }

    bool isCyclicUndirected() {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (isCyclicUndirectedUtil(i, -1, visited))
                    return true;
            }
        }
        return false;
    }

    bool isCyclicDirectedUtil(int node, vector<bool>& visited, vector<bool>& recStack) {
        visited[node] = true;
        recStack[node] = true;

        for (auto& neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (isCyclicDirectedUtil(neighbor, visited, recStack))
                    return true;
            } else if (recStack[neighbor]) {
                return true;
            }
        }

        recStack[node] = false;
        return false;
    }

    bool isCyclicDirected() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (isCyclicDirectedUtil(i, visited, recStack))
                    return true;
            }
        }

        return false;
    }
};

// ==== MENU ====
int main() {
    int V, choice, u, v, directedFlag;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Is the graph directed? (1 for Yes, 0 for No): ";
    cin >> directedFlag;

    Graph g(V, directedFlag);

    while (true) {
        cout << "\n=== Graph Menu ===\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Detect Cycle (Undirected)\n";
        cout << "4. Detect Cycle (Directed)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
            break;

        case 2:
            g.printGraph();
            break;

        case 3:
            if (directedFlag) {
                cout << "This is a directed graph. Choose option 4.\n";
            } else {
                if (g.isCyclicUndirected())
                    cout << "Cycle Detected (Undirected Graph)\n";
                else
                    cout << "No Cycle (Undirected Graph)\n";
            }
            break;

        case 4:
            if (!directedFlag) {
                cout << "This is an undirected graph. Choose option 3.\n";
            } else {
                if (g.isCyclicDirected())
                    cout << "Cycle Detected (Directed Graph)\n";
                else
                    cout << "No Cycle (Directed Graph)\n";
            }
            break;

        case 5:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
