#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// max height is 40. 4 piles.
int n;
int piles[4][45];
int memo[45][45][45][45];

// find max candies bob can get
int solve(int h1, int h2, int h3, int h4, int mask, int basket_size) {
    // basket full. stop here.
    if (basket_size == 5) return 0;
    
    // check if we did this before
    if (memo[h1][h2][h3][h4] != -1) return memo[h1][h2][h3][h4];

    int max_pairs = 0;
    int heights[4] = {h1, h2, h3, h4};

    // try pick from each pile
    for (int i = 0; i < 4; ++i) {
        if (heights[i] < n) {
            int color = piles[i][heights[i]];
            int next_h[4] = {h1, h2, h3, h4};
            next_h[i]++;

            // if color in basket, we get a pair!
            if ((mask >> color) & 1) {
                // remove from basket mask. pair found +1.
                int res = 1 + solve(next_h[0], next_h[1], next_h[2], next_h[3], mask ^ (1 << color), basket_size - 1);
                max_pairs = max(max_pairs, res);
            } else {
                // add to basket mask.
                int res = solve(next_h[0], next_h[1], next_h[2], next_h[3], mask | (1 << color), basket_size + 1);
                max_pairs = max(max_pairs, res);
            }
        }
    }

    // save result
    return memo[h1][h2][h3][h4] = max_pairs;
}

int main() {
    // read n until 0
    while (cin >> n && n != 0) {
        // load piles. transpose for easy access.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 4; ++j) {
                cin >> piles[j][i];
            }
        }
        memset(memo, -1, sizeof(memo));

        // start game from top of piles
        cout << solve(0, 0, 0, 0, 0, 0) << endl;
    }
    return 0;
}