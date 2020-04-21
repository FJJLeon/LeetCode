#include<vector>
#include<limits.h>

using namespace std;

class BinaryMatrix {
  public:
    int get(int x, int y);
    vector<int> dimensions();
};

/**
 * 强行不给 direct access, 用 function call 来统计元素访问次数，卡掉 O(N*M) 100*100 at most...
 * each row is non-decreasing order
 * 1. so binary search for each row to find leftmost one's index is ok, O(T) = O(N*logM), exectly 100*log100 = 1000 access at most
 * another fact can be exploited is that if you find one in a column, then the rest of this column is useless, no necessary to access later
 * 2. traverse from top-right elem,
 *  a. if 1, update and go left
 *  b. if 0, go down
 *  c. loop until encounter left or lower border and stop
 * O(T) = O(N+M) 200 at most
 * 
 * Runtime: 8 ms, O(N+M)
 * Memory Usage: 8.1 MB, O(1)
*/
class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dim = binaryMatrix.dimensions();
        int n = dim[0], m = dim[1];
        int x = 0, y = m-1;
        
        int res = INT_MAX;
        while (x < n && y >= 0) {
            if (binaryMatrix.get(x, y) == 1) {
                // update
                res = y;
                // go left
                --y;
            }
            else {
                // go down
                ++x;
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
