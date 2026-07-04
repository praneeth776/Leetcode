#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

// global max for small constraints
int n, m, source, sink;
int capacity[105][105], flow[105][105], parent[105];

// find if more flow can go through
bool bfs() {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(source);
    parent[source] = source;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v <= sink; v++) {
            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                parent[v] = u;
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
}

// standard max flow logic
int max_flow() {
    int total = 0;
    memset(flow, 0, sizeof(flow));
    while (bfs()) {
        int path_flow = 1e9;
        for (int v = sink; v != source; v = parent[v]) {
            path_flow = min(path_flow, capacity[parent[v]][v] - flow[parent[v]][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            flow[parent[v]][v] += path_flow;
            flow[v][parent[v]] -= path_flow;
        }
        total += path_flow;
    }
    return total;
}

void solve(int t) {
    cin >> n >> m;
    source = 0; sink = n + m + 1;
    memset(capacity, 0, sizeof(capacity));
    
    vector<int> spots(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> spots[i];
        capacity[n + i][sink] = spots[i]; // projects to sink
    }
    
    vector<vector<int>> prefs(n + 1);
    for (int i = 1; i <= n; i++) {
        int k; cin >> k;
        while (k--) {
            int p; cin >> p;
            prefs[i].push_back(p);
            capacity[i][n + p] = 1; // candidate to project
        }
        capacity[source][i] = 1; // source to candidate
    }
    
    int global_max = max_flow();
    vector<pair<int, int>> final_hiring;
    
    // greedy check for each rank
    for (int i = 1; i <= n; i++) {
        bool assigned = false;
        // remove source link temporarily to "pick" this guy
        capacity[source][i] = 0;
        
        for (int p : prefs[i]) {
            // try assigning candidate i to project p
            int old_proj_cap = capacity[n + p][sink];
            if (old_proj_cap > 0) {
                capacity[n + p][sink]--; // use one spot
                
                // see if we can still hit the target with others
                int current_max = max_flow();
                if (current_max + final_hiring.size() + 1 == global_max) {
                    final_hiring.push_back({i, p});
                    assigned = true;
                    // project spots permanently reduced for later ranks
                    break;
                }
                capacity[n + p][sink]++; // backtrack
            }
        }
        
        // if no good project for him, he is not part of the max set
        if (!assigned) {
            // check if we still need him for max count later
            capacity[source][i] = 1;
            if (max_flow() + final_hiring.size() < global_max) {
                // this shouldn't happen if global_max is correct
            } else {
                capacity[source][i] = 0; // he cant be used
            }
        }
    }
    
    cout << "Case #" << t << ":" << endl;
    cout << global_max << " applicant(s) can be hired." << endl;
    for (auto& h : final_hiring) {
        cout << h.first << " " << h.second << endl;
    }
}

int main() {
    int t_cases; cin >> t_cases;
    for (int i = 1; i <= t_cases; i++) solve(i);
    return 0;
}