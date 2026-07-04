#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// global array for distanses. 101 because nodes 1-100.
int dist[101][101];
const int INF = 1e7;

void solve() {
    int u, v, caseNum = 1;
    
    // loop until first number is 0
    while (cin >> u >> v && (u != 0 || v != 0)) {
        // init distanse matrix with big number
        for (int i = 1; i <= 100; ++i) {
            for (int j = 1; j <= 100; ++j) {
                dist[i][j] = INF;
            }
            dist[i][i] = 0;
        }

        // track which nodes actually exists in this test case
        vector<bool> exists(101, false);
        
        // add first edge
        dist[u][v] = 1;
        exists[u] = exists[v] = true;

        // read more edges until 0 0
        while (cin >> u >> v && (u != 0 || v != 0)) {
            dist[u][v] = 1;
            exists[u] = exists[v] = true;
        }

        // floyd warshall algorithm for all pairs shortest path
        for (int k = 1; k <= 100; ++k) {
            if (!exists[k]) continue;
            for (int i = 1; i <= 100; ++i) {
                if (!exists[i]) continue;
                for (int j = 1; j <= 100; ++j) {
                    if (!exists[j]) continue;
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        double totalSum = 0;
        int pairCount = 0;
        
        // sum up shortest paths for all valid pairs
        for (int i = 1; i <= 100; ++i) {
            for (int j = 1; j <= 100; ++j) {
                if (exists[i] && exists[j] && i != j) {
                    totalSum += dist[i][j];
                    pairCount++;
                }
            }
        }

        // calculate average and print with 3 decimal places
        double avg = totalSum / pairCount;
        cout << "Case " << caseNum++ << ": average length between pages = " 
             << fixed << setprecision(3) << avg << " clicks" << endl;
    }
}

int main() {
    solve();
    return 0;
}