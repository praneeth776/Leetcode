#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 ** This problem requires a Topological Sort using Kahn's Algorithm.
 **/

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        in_degree[y]++;
    }

    // Min-priority queue ensures we always pick the smallest available task index
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        result.push_back(u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                pq.push(v);
            }
        }
    }

    if (result.size() < n) {
        cout << "Sandro fails." << endl;
    } 
    else {
        for (int i = 0; i < n-1; ++i) {
            cout << result[i] << " ";
        }
        cout << result[n-1] << endl;
    }

    return 0;
}