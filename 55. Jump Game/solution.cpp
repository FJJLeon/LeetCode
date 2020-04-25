#include<vector>

using namespace std;

/**
 * DP top-down
 * traverse backwards, record whether index i can 'reach' last directly or indirectly
 * 
 * howerer, TLE in worst case like [5,4,3,2,1,0,0]
*/
class Solution1 {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        vector<bool> can(len, false);
        can[len - 1] = true;
        for (int i = len - 2; i >= 0; --i) {
            for (int j = 0; j <= nums[i] && i + j < len && !can[i]; ++j) {
                can[i] = can[i] | can[i + j];
            }
        }
        return can[0];
    }
};

/**
 * Greedy
 * 
 * Runtime: 8 ms, faster than 93.89%, O(N)
 * Memory Usage: 8.1 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        // smallest index that can reach last
        int last = n - 1;

        for (int i = n - 2; i >= 0; --i) {
            if (i + nums[i] >= last)
                last = i;
        }
        return last == 0;
    }
};
