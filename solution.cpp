#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
};

bool cmpX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool cmpY(const Point& a, const Point& b) {
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Point> points;
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    // Sort by x-coordinate
    sort(points.begin(), points.end(), cmpX);
    
    // Create coordinate mappings for efficient lookup
    vector<int> x_coords, y_coords;
    for (const auto& p : points) {
        x_coords.push_back(p.x);
        y_coords.push_back(p.y);
    }
    
    // Sort y-coordinates for binary search
    sort(y_coords.begin(), y_coords.end());
    
    long long result = 0;
    
    // Check all pairs of points where one could be bottom-left of the other
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].y < points[j].y) {
                bool isEmpty = true;
                
                // Check if any point lies inside the rectangle
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    
                    // Check if point k is inside or on boundary
                    if (points[k].x >= points[i].x && points[k].x <= points[j].x &&
                        points[k].y >= points[i].y && points[k].y <= points[j].y) {
                        // Exclude the corners
                        if (!((points[k].x == points[i].x && points[k].y == points[i].y) ||
                              (points[k].x == points[j].x && points[k].y == points[j].y))) {
                            isEmpty = false;
                            break;
                        }
                    }
                }
                
                if (isEmpty) {
                    result++;
                }
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}