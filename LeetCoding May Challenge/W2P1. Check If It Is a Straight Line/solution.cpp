#include<vector>

using namespace std;

/**
 * y = kx * d
 * Runtime: 20 ms, faster than 14.27%, O(N)
 * Memory Usage: 10.6 MB, less than 100.00%, O(1)
*/
class Solution1 {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        // y = kx + d, k != inf
        double k, d;
        // check line vertical to the x axis
        int x1 = coordinates.front()[0], y1 = coordinates.front()[1];
        bool vertical = true;
        for (auto point : coordinates) {
            if (point[0] != x1) {
                vertical = false;
                
                k = (point[1] - y1) / (point[0] - x1);
                d = y1 - k * x1;
            }
        }
        
        if (vertical)
            return true;
        
        for (auto point : coordinates) {
            if (point[1] != k * point[0] + d)
                return false;
        }
        
        return true;
    }
};

/**
 * convert to check multiplication
 * avoid divid by zero error
 * 
 * Runtime: 20 ms, faster than 14.27%, O(N)
 * Memory Usage: 10 MB, less than 100.00%, O(1)
*/
class Solution2 {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        // (y1 - y0) / (x1 - x0) = (yN - y0) / (xN - x0)
        // dy = y1 - y0, dx = x1 - x0
        // dy * (xN - x0) = dx * (yN - y0)
        double dy = coordinates.back()[1] - coordinates.front()[1],
               dx = coordinates.back()[0] - coordinates.front()[0];
        int y0 = coordinates.front()[1],
            x0 = coordinates.front()[0];
        for (auto point : coordinates) {
            if (dy * (point[0] - x0) != dx * (point[1] - y0))
                return false;
        }
        
        return true;
    }
};
