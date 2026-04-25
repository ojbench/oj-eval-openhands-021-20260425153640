#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
};

bool cmpX(const Point& a, const Point& b) {
    return a.x < b.x;
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
    
    // Create coordinate compression
    vector<int> x_coords, y_coords;
    for (const auto& p : points) {
        x_coords.push_back(p.x);
        y_coords.push_back(p.y);
    }
    
    sort(y_coords.begin(), y_coords.end());
    
    // Map y-coordinates to compressed indices
    unordered_map<int, int> y_to_idx;
    for (int i = 0; i < n; i++) {
        y_to_idx[y_coords[i]] = i;
    }
    
    // Create 2D grid for prefix sum
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (const auto& p : points) {
        int x_idx = lower_bound(x_coords.begin(), x_coords.end(), p.x) - x_coords.begin();
        int y_idx = y_to_idx[p.y];
        grid[x_idx][y_idx] = 1;
    }
    
    // Create 2D prefix sum array
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = grid[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }
    
    auto countPointsInRectangle = [&](int x1, int y1, int x2, int y2) {
        // Convert to prefix sum coordinates (1-based)
        x1 = lower_bound(x_coords.begin(), x_coords.end(), x1) - x_coords.begin() + 1;
        x2 = lower_bound(x_coords.begin(), x_coords.end(), x2) - x_coords.begin() + 1;
        y1 = y_to_idx[y1] + 1;
        y2 = y_to_idx[y2] + 1;
        
        return prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1];
    };
    
    long long result = 0;
    
    // Check all pairs of points where one could be bottom-left of the other
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].y < points[j].y) {
                // Count points in the rectangle (including boundaries)
                int pointsInRect = countPointsInRectangle(points[i].x, points[i].y, points[j].x, points[j].y);
                
                // If only the two corner points are in the rectangle, it's valid
                if (pointsInRect == 2) {
                    result++;
                }
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}