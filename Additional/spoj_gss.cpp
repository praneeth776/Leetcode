#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// structure for segment tree node
struct Node {
    long long maxSub;
    long long pref;
    long long suff;
    long long sum;

    // constructor for a single element
    Node(long long val = -1e18) {
        sum = val;
        maxSub = pref = suff = val;
    }
};

// combine left and right child to make parent
Node combine(Node L, Node R) {
    if (L.sum <= -1e17) return R; // if left is empty/null
    if (R.sum <= -1e17) return L; // if right is empty/null

    Node parent;
    parent.sum = L.sum + R.sum;
    // prefix is either left's prefix or left's sum + right's prefix
    parent.pref = max(L.pref, L.sum + R.pref);
    // suffix is either right's suffix or right's sum + left's suffix
    parent.suff = max(R.suff, R.sum + L.suff);
    // maxSub is the best of: left side, right side, or crossing the middle
    parent.maxSub = max({L.maxSub, R.maxSub, L.suff + R.pref});
    
    return parent;
}

int N, M;
long long arr[50005];
Node tree[200005];

// build the tree at start
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = Node(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

// update value at index idx
void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = Node(val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

// query the range [l, r]
Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return Node(-1e18); // out of range
    if (l <= start && end <= r) return tree[node];

    int mid = (start + end) / 2;
    Node p1 = query(2 * node, start, mid, l, r);
    Node p2 = query(2 * node + 1, mid + 1, end, l, r);
    
    return combine(p1, p2);
}

int main() {
    // speed up cin
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    build(1, 1, N);

    cin >> M;
    while (M--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0) {
            update(1, 1, N, x, (long long)y);
        } else {
            Node res = query(1, 1, N, x, y);
            cout << res.maxSub << "\n";
        }
    }

    return 0;
}