#include<vector>

using namespace std;

/**
 * like DP
 * 
 * Runtime: 0 ms, faster than 100.00%, O(rowIndex^2)
 * Memory Usage: 6 MB, less than 100.00%, O(rowIndex)
*/
class Solution1 {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res;
        for (int i = 0; i <= rowIndex; ++i) {
            res.push_back(1);
            for (int j = i - 1; j > 0; --j) {
                res[j] += res[j - 1];
            }
        }
        return res;
    }
};