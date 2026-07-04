#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// global stuff for tree
vector<int> adj[1005];
int parent[1005];
int depth[1005];

// find how deep every node is
void find_depth(int u, int d) {
    depth[u] = d;
    for (int i = 0; i < adj[u].size(); ++i) {
        find_depth(adj[u][i], d + 1);
    }
}

// find the lca of u and v
int get_lca(int u, int v) {
    // move u up if it is deeper
    while (depth[u] > depth[v]) {
        u = parent[u];
    }
    // move v up if it is deeper
    while (depth[v] > depth[u]) {
        v = parent[v];
    }
    // move both up until they meet
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

void solve(int t) {
    int n;
    cin >> n;

    // reset tree for new case
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        parent[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int child;
            cin >> child;
            adj[i].push_back(child);
            parent[child] = i;
        }
    }

    // root has no parent. find it.
    int root = 1;
    for (int i = 1; i <= n; ++i) {
        if (parent[i] == 0) {
            root = i;
            break;
        }
    }

    find_depth(root, 0);

    int q;
    cin >> q;
    cout << "Case " << t << ":" << endl;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << get_lca(u, v) << endl;
    }
}

int main() {
    int test_cases;
    if (!(cin >> test_cases)) return 0;
    for (int i = 1; i <= test_cases; ++i) {
        solve(i);
    }
    return 0;
}