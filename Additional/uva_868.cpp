#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// global vars for grid size and the grid itself
int rows, cols; 
int maze[105][105];
int exit_col;
bool win;

// up, down, left, right moves 
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// dfs to find path based on weird 1, 1-2, 1-2-3 rule 
void walk(int r, int c, int cur, int target) {
    // hit the bottom row! 
    if (r == rows - 1) {
        if (!win || c < exit_col) {
            exit_col = c;
        }
        win = true;
        // keep looking for better exit 
    }

    int next_v, next_t;
    // update numbers for next step
    if (cur < target) {
        next_v = cur + 1;
        next_t = target;
    } else {
        next_v = 1;
        next_t = target + 1;
    }

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // check if inside maze
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            // number must match the rule 
            if (maze[nr][nc] == next_v) {
                walk(nr, nc, next_v, next_t);
            }
        }
    }
}

void solve_maze() {
    if (!(cin >> rows >> cols)) return;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> maze[i][j];
        }
    }

    win = false;
    // check top row for start 
    for (int j = 0; j < cols; j++) {
        if (maze[0][j] == 1) {
            exit_col = 1000; // big number for min search
            walk(0, j, 1, 1);
            if (win) {
                // print top and bottom coordinates [cite: 256]
                cout << 1 << " " << j + 1 << endl;
                cout << rows << " " << exit_col + 1 << endl;
                return; // stop at first smallest start 
            }
        }
    }
}

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve_maze();
        if (t > 0) cout << endl; // blank line rule [cite: 255]
    }
    return 0;
}