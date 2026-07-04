#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// max N is 100,000. log2 of 100,000 is about 17.
const int MAXN = 100005;
const int K = 18;
int st[MAXN][K];
int lg[MAXN];

int main() {
    // optimize i/o speed
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // precompute logs for O(1) query
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i/2] + 1;

    // read initial numbers into power 0
    for (int i = 0; i < n; i++) {
        cin >> st[i][0];
    }

    // build the sparse table
    for (int j = 1; j < K; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            // min of two halves
            st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j-1]);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        // make sure l is smaller than r
        if (l > r) swap(l, r);
        
        int j = lg[r - l + 1];
        // answer is min of two overlapping ranges
        int ans = min(st[l][j], st[r - (1 << j) + 1][j]);
        cout << ans << "\n";
    }

    return 0;
}