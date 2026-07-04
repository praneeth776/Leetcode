#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// pi is important for circles
const double PI = acos(-1.0);

// find volume from x_low to h
double get_vol(const vector<double>& poly, double low, double h) {
    double v = 0;
    // integrate the squared polynomial: integral of a*x^i is (a/(i+1))*x^(i+1)
    for (int i = 0; i < poly.size(); i++) {
        v += (poly[i] / (i + 1)) * (pow(h, i + 1) - pow(low, i + 1));
    }
    return v * PI;
}

void solve_bottle() {
    int n, case_num = 1;
    // read degree n until end
    while (cin >> n) {
        vector<double> a(n + 1);
        for (int i = 0; i <= n; i++) cin >> a[i];

        double x_low, x_high;
        int inc;
        cin >> x_low >> x_high >> inc;

        // square the polynomial P(x) to get P(x)^2
        // because volume formula is integral of PI * r^2
        vector<double> a_sq(2 * n + 1, 0.0);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                a_sq[i + j] += a[i] * a[j];
            }
        }

        // total volume of the bottle
        double total_v = get_vol(a_sq, x_low, x_high);

        cout << "Case " << case_num++ << ": " << fixed << setprecision(2) << total_v << endl;

        vector<double> marks;
        double current_target = inc;

        // find up to 8 marks
        for (int k = 0; k < 8; k++) {
            if (current_target > total_v) break;

            // binary search for height h that gives current_target volume
            double low = x_low, high = x_high;
            // 100 times is enough for precision
            for (int iter = 0; iter < 100; iter++) {
                double mid = (low + high) / 2.0;
                if (get_vol(a_sq, x_low, mid) < current_target) low = mid;
                else high = mid;
            }
            
            // answer is distance UP from bottom
            marks.push_back(low - x_low);
            current_target += inc;
        }

        if (marks.empty()) {
            cout << "insufficient volume" << endl;
        } else {
            for (int i = 0; i < marks.size(); i++) {
                cout << fixed << setprecision(2) << marks[i] << (i == marks.size() - 1 ? "" : " ");
            }
            cout << endl;
        }
    }
}

int main() {
    // make it go fast
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve_bottle();
    return 0;
}