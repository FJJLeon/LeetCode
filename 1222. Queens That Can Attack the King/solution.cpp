#include<vector>
#include<unordered_set>

using namespace std;

/**
 * check 8 direction of king, search the nearest queen
 * 
 * Runtime: 4 ms, faster than 92.43%, O(Q + 8*8), Q = len(queens)
 * Memory Usage: 7.3 MB, less than 100.00%, O(Q)
*/
class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<vector<int>> res;
        // store queens for search
        unordered_set<int> qs;
        for (auto& v : queens) {
            qs.insert(encode(v[0], v[1]));
        }
        // 8 direction (dx, dy)
        const vector<vector<int>> direct = {
            {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
            {1, 0}, {1, -1}, {0, -1}, {-1, -1}
        };
        int kx = king[0], ky = king[1];
        // check each direction
        for (auto& d : direct) {
            int dx = d[0], dy = d[1];

            int x = kx + dx, y = ky + dy;
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (qs.find(encode(x, y)) != qs.end()) {
                    // find nearest queen and break
                    res.push_back(vector<int>{x, y});
                    break;
                }
                x += dx;
                y += dy;
            }
        }
        
        return res;
    }
private:
    inline int encode(int x, int y) {
        return 8 * x + y;
    }
};
