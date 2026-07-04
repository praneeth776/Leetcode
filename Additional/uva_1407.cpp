#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// structure for paths between caves
struct Edge {
    int to, dist;
};

vector<Edge> adj[505];
int node_count;
// dp[u][k][0]: min dist to visit k nodes in subtree u and return to u
// dp[u][k][1]: min dist to visit k nodes in subtree u and NOT return
int dp[505][505][2];
int sz[505];

const int INF = 1e9;

// tree dp function
void dfs(int u) {
    sz[u] = 1;
    dp[u][1][0] = dp[u][1][1] = 0; // visit self costs nothing

    for (auto& edge : adj[u]) {
        int v = edge.to;
        int d = edge.dist;
        dfs(v);

        // combine current subtree results with child results
        for (int i = min(node_count, sz[u] + sz[v]); i >= 2; --i) {
            for (int j = 1; j <= sz[v] && j < i; ++j) {
                // case 0: return to u
                // must return to u from both previous caves and new branch
                dp[u][i][0] = min(dp[u][i][0], dp[u][i - j][0] + dp[v][j][0] + 2 * d);

                // case 1: dont return to u
                // choice 1: return from previous branches, stay in this new branch v
                dp[u][i][1] = min(dp[u][i][1], dp[u][i - j][0] + dp[v][j][1] + d);
                // choice 2: stay in one of the previous branches, must return from branch v
                dp[u][i][1] = min(dp[u][i][1], dp[u][i - j][1] + dp[v][j][0] + 2 * d);
            }
        }
        sz[u] += sz[v];
    }
}

void solve() {
    int case_num = 1;
    while (cin >> node_count && node_count != 0) {
        // clear old data
        for (int i = 0; i < node_count; i++) {
            adj[i].clear();
            for (int j = 0; j <= node_count; j++) {
                dp[i][j][0] = dp[i][j][1] = INF;
            }
        }

        // build tree from input
        for (int k = 0; k < node_count - 1; k++) {
            int i, j, d;
            cin >> i >> j >> d; // i is child, j is parent
            adj[j].push_back({i, d});
        }

        // main cave is always 0
        dfs(0);

        int q;
        cin >> q;
        cout << "Case " << case_num++ << ":" << endl;
        while (q--) {
            int energy;
            cin >> energy;
            int max_caves = 0;
            // find biggest k where robot has enough energy
            for (int k = node_count; k >= 1; k--) {
                if (dp[0][k][1] <= energy) {
                    max_caves = k;
                    break;
                }
            }
            cout << max_caves << endl;
        }
    }
}

int main() {
    // start code
    solve();
    return 0;
}