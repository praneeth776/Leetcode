#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// structure for points in 2D
struct Point {
    double x, y;
};

// cross product helps determine which side of a line a point lies on 
double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// find intersection point of line segment (a,b) and cutting line (p1,p2) 
Point get_intersection(Point a, Point b, Point p1, Point p2) {
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = a1 * a.x + b1 * a.y;
    
    double a2 = p2.y - p1.y;
    double b2 = p1.x - p2.x;
    double c2 = a2 * p1.x + b2 * p1.y;
    
    double determinant = a1 * b2 - a2 * b1;
    return {(b2 * c1 - b1 * c2) / determinant, (a1 * c2 - a2 * c1) / determinant};
}

// clip the polygon using the water line, keeping the part with the fountain
vector<Point> clip_polygon(const vector<Point>& polygon, Point p1, Point p2, Point fountain) {
    vector<Point> new_polygon;
    int size = polygon.size();
    if (size == 0) return new_polygon;

    // find which side of the water line the fountain is on 
    double fountain_side = cross_product(p1, p2, fountain);

    for (int i = 0; i < size; ++i) {
        Point current = polygon[i];
        Point next = polygon[(i + 1) % size];
        
        double current_side = cross_product(p1, p2, current);
        double next_side = cross_product(p1, p2, next);

        // if current point is on fountain side
        if (current_side * fountain_side >= 0) {
            if (next_side * fountain_side < 0) {
                // edge crosses line going outward
                new_polygon.push_back(get_intersection(current, next, p1, p2));
            }
        } else if (next_side * fountain_side >= 0) {
            // edge crosses line going inward
            new_polygon.push_back(get_intersection(current, next, p1, p2));
        }
        
        // always keep the next point if it is on the fountain side
        if (next_side * fountain_side >= 0) {
            new_polygon.push_back(next);
        }
    }
    return new_polygon;
}

void solve() {
    int num_lines, case_idx = 1;
    double width, height, fountain_x, fountain_y;

    // read test case header [cite: 222]
    while (cin >> num_lines >> width >> height >> fountain_x >> fountain_y) {
        Point fountain = {fountain_x, fountain_y};
        vector<Point> current_piece;

        // start with the full rectangular garden boundary 
        current_piece.push_back({0, 0});
        current_piece.push_back({width, 0});
        current_piece.push_back({width, height});
        current_piece.push_back({0, height});

        for (int i = 0; i < num_lines; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2; // read water line endpoints 
            current_piece = clip_polygon(current_piece, {x1, y1}, {x2, y2}, fountain);
        }

        // shoelace formula for area calculation 
        double total_area = 0;
        int p_size = current_piece.size();
        for (int i = 0; i < p_size; ++i) {
            total_area += (current_piece[i].x * current_piece[(i + 1) % p_size].y - 
                          current_piece[(i + 1) % p_size].x * current_piece[i].y);
        }
        
        // output with 3 decimal places 
        cout << "Case #" << case_idx++ << ": " << fixed << setprecision(3) << abs(total_area) / 2.0 << endl;
    }
}

int main() {
    // optimize I/O speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}