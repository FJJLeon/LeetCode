#include<vector>

using namespace std;

/**
 * DP Bottom-up
 * traverse backwards, record whether index i can 'reach' last index directly or indirectly
 * 
 * Runtime: O(N^2), howerer, TLE in worst case like [5,4,3,2,1,0,0]
 * Space: O(N)
*/
class Solution1 {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        vector<bool> can(len, false);
        // last index can reach itself trivially
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
 *  从 Bottom-up DP 中可以看到，一旦确定可以跳到最后，就可以 break 内循环(!can[i])，也就是说只用了最左边的跳板（或者不需要跳板）
 *  这样的话，应用贪心算法，我们只要从右到左迭代并记录这种最近(最左边)的跳板，只要开始节点也是这样的跳板即可
 *  
 *  对于 nums = [9, 4, 2, 1, 0, 2, 0]
 *  贪心会选择 9-4-2-0 路径，虽然 9-0 也是正确的路径
 * 
 * Runtime: 8 ms, faster than 93.89%, O(N)
 * Memory Usage: 8.1 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        // smallest index that can reach last， first jumpboard is last index itself
        int last = n - 1;

        for (int i = n - 2; i >= 0; --i) {
            // find nearest jumpboard
            if (i + nums[i] >= last)
                last = i;
        }
        return last == 0;
    }
};
