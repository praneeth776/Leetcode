#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x, y, z;
};

double get_dist(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

int main() {
    int n, caseNum = 1;
    while (cin >> n && n != 0) {
        Point c1, c2;
        cin >> c1.x >> c1.y >> c1.z >> c2.x >> c2.y >> c2.z;

        double minX = min(c1.x, c2.x), maxX = max(c1.x, c2.x);
        double minY = min(c1.y, c2.y), maxY = max(c1.y, c2.y);
        double minZ = min(c1.z, c2.z), maxZ = max(c1.z, c2.z);

        double boxVol = (maxX - minX) * (maxY - minY) * (maxZ - minZ);
        vector<Point> pts(n);
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y >> pts[i].z;
            p[i] = i;
        }

        double maxBallVol = 0;

        // Check all n! permutations
        do {
            vector<double> radii(n, 0.0);
            double currentVol = 0;

            for (int i = 0; i < n; ++i) {
                int idx = p[i];
                Point cur = pts[idx];

                // Check if point is outside
                if (cur.x < minX || cur.x > maxX || cur.y < minY || cur.y > maxY || cur.z < minZ || cur.z > maxZ) {
                    radii[idx] = 0;
                    continue;
                }

                // Max radius limited by walls
                double r = cur.x - minX;
                r = min(r, maxX - cur.x);
                r = min(r, cur.y - minY);
                r = min(r, maxY - cur.y);
                r = min(r, cur.z - minZ);
                r = min(r, maxZ - cur.z);

                // Max radius limited by previous balloons
                for (int j = 0; j < i; ++j) {
                    int prevIdx = p[j];
                    double d = get_dist(cur, pts[prevIdx]);
                    r = min(r, d - radii[prevIdx]);
                }

                if (r < 0) r = 0;
                radii[idx] = r;
                currentVol += (4.0 / 3.0) * M_PI * r * r * r;
            }
            if (currentVol > maxBallVol) maxBallVol = currentVol;

        } while (next_permutation(p.begin(), p.end()));

        // Round to nearest integer
        double finalVol = boxVol - maxBallVol;
        cout << "Box " << caseNum++ << ": " << (long long)(finalVol + 0.5) << endl << endl;
    }
    return 0;
}