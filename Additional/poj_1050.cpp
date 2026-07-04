#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


int kadane(const vector<int>& arr) {
    int max_so_far = INT_MIN;
    int current_max = 0;
    
    for (int x : arr) {
        current_max += x;
        if (max_so_far < current_max)
            max_so_far = current_max;
        if (current_max < 0)
            current_max = 0;
    }
    return max_so_far;
}

int main() {
    int n;
    // read n and check if input exists
    if (!(cin >> n)) return 0;

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    int global_max = INT_MIN;

    // fix top row
    for (int top = 0; top < n; top++) {
        // temp array to store col sums between top and bottom
        vector<int> col_sums(n, 0);
        
        // fix bottom row
        for (int bottom = top; bottom < n; bottom++) {
            for (int col = 0; col < n; col++) {
                col_sums[col] += matrix[bottom][col];
            }
            
            // run 1D kadane on current vertical slice
            global_max = max(global_max, kadane(col_sums));
        }
    }

    // print the biggest sum found
    cout << global_max << endl;

    return 0;
}