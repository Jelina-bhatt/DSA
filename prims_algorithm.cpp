#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

void primsMST(vector<pii> adj[], int V) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);

    key[0] = 0;
    pq.push({0, 0}); // {weight, vertex}

    int mstCost = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        mstCost += key[u];

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (!inMST[v] && key[v] > w) {
                key[v] = w;
                pq.push({w, v});
            }
        }
    }

    cout << "Total cost of MST: " << mstCost << endl;
}

int main() {
    int V = 5;
    vector<pii> adj[V];

    // Undirected Graph - Add both directions
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    adj[3].push_back({4, 9});
    adj[4].push_back({3, 9});

    primsMST(adj, V);
    return 0;
}
