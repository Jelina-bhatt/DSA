#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent a connected component with resistance
struct Edge {
    int to;
    int resistance;
};

// Dijkstra's Algorithm to find the least-resistance path
void dijkstra(int start, vector<vector<Edge>>& graph, vector<int>& minResistance) {
    int n = graph.size();
    minResistance.assign(n, INT_MAX);
    minResistance[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start}); // {resistance, node}

    while (!pq.empty()) {
        int current = pq.top().second;
        int currRes = pq.top().first;
        pq.pop();

        if (currRes > minResistance[current]) continue;

        for (auto& edge : graph[current]) {
            int next = edge.to;
            int res = edge.resistance;

            if (minResistance[next] > currRes + res) {
                minResistance[next] = currRes + res;
                pq.push({minResistance[next], next});
            }
        }
    }
}

int main() {
    int nodes = 6;
    vector<vector<Edge>> circuitGraph(nodes);

    // Add connections (from, to, resistance)
    circuitGraph[0].push_back({1, 5});
    circuitGraph[0].push_back({2, 3});
    circuitGraph[1].push_back({3, 8});
    circuitGraph[2].push_back({3, 2});
    circuitGraph[3].push_back({4, 1});
    circuitGraph[4].push_back({5, 4});

    vector<int> minResistance;
    int source = 0;
    dijkstra(source, circuitGraph, minResistance);

    cout << "Minimum resistance from node " << source << " to other nodes:\n";
    for (int i = 0; i < nodes; ++i) {
        if (minResistance[i] == INT_MAX)
            cout << "Node " << i << ": Unreachable\n";
        else
            cout << "Node " << i << ": " << minResistance[i] << " ohms\n";
    }

    return 0;
}
