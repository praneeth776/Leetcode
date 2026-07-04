#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Square {
    char val;
    int num;
};

void solve() {
    int r, c, puzzleNum = 1;
    while (cin >> r && r != 0) {
        cin >> c;
        vector<vector<Square>> grid(r, vector<Square>(c));
        int currentNum = 1;

        // Reading grid and assign numbers
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> grid[i][j].val;
                grid[i][j].num = 0;

                if (grid[i][j].val != '*') {
                    // Check eligibility for a number
                    if (i == 0 || j == 0 || grid[i - 1][j].val == '*' || grid[i][j - 1].val == '*') {
                        grid[i][j].num = currentNum++;
                    }
                }
            }
        }

        if (puzzleNum > 1) cout << endl;
        cout << "puzzle #" << puzzleNum++ << ":" << endl;

        // Extracting Across Words
        cout << "Across" << endl;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j].val != '*' && (j == 0 || grid[i][j - 1].val == '*')) {
                    cout << setw(3) << grid[i][j].num << ".";
                    int tempJ = j;
                    while (tempJ < c && grid[i][tempJ].val != '*') {
                        cout << grid[i][tempJ].val;
                        tempJ++;
                    }
                    cout << endl;
                }
            }
        }

        // Extracting Down Words
        cout << "Down" << endl;
        // We must output words in increasing order of their definition numbers
        // Since Down words can start on any row, we scan row-by-row to find the lowest numbers first
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j].val != '*' && (i == 0 || grid[i - 1][j].val == '*')) {
                    cout << setw(3) << grid[i][j].num << ".";
                    int tempI = i;
                    while (tempI < r && grid[tempI][j].val != '*') {
                        cout << grid[tempI][j].val;
                        tempI++;
                    }
                    cout << endl;
                }
            }
        }
    }
}

int main() {
    solve();
    return 0;
}