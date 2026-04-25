#include <iostream>
#include <vector>
#include <algorithm>
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
    
    long long result = 0;
    
    // Check all pairs of points where one could be bottom-left of the other
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].y < points[j].y) {
                bool isEmpty = true;
                
                // Check if any point lies strictly inside the rectangle
                for (int k = i + 1; k < j; k++) {
                    if (points[k].y > points[i].y && points[k].y < points[j].y) {
                        isEmpty = false;
                        break;
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