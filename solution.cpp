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
    
    long long result = 0;
    
    // For each point as the right boundary
    for (int j = 0; j < n; j++) {
        // Collect all points to the left of j
        vector<pair<int, int>> left_points;
        for (int i = 0; i < j; i++) {
            if (points[i].y < points[j].y) {
                left_points.emplace_back(points[i].y, i);
            }
        }
        
        // Sort left points by y-coordinate
        sort(left_points.begin(), left_points.end());
        
        // Use a set to track x-indices of points seen so far
        set<int> seen_x;
        
        // Process left points in order of increasing y
        for (const auto& [y, x_idx] : left_points) {
            // Check if there are any points between x_idx and j with y between current y and points[j].y
            bool has_obstacle = false;
            for (int k = x_idx + 1; k < j; k++) {
                if (points[k].y > y && points[k].y < points[j].y) {
                    has_obstacle = true;
                    break;
                }
            }
            
            if (!has_obstacle) {
                result++;
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}