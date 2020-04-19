#include<vector>

using namespace std;

/**
 * there must be one half part is sorted
 *  1. nums[lo] <= nums[mid], left part is sorted:
 *      1a. nums[lo] <= target < nums[mid], target in left part
 *      1b. not 1a, target in right part
 *  2. not 1, right part is sorted:
 *      2a. nums[mid] < target <= nums[hi], target in right part
 *      2b. not 2a, target in left part
 * 
 * Runtime: 4 ms, faster than 67.77%, O(logN)
 * Memory Usage: 6.6 MB, less than 100.00%
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target)
                return mid;
            // left part is sorted
            if (nums[lo] <= nums[mid]) {
                // target in left part
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;
                // target in right part
                else
                    lo = mid + 1;
            }
            // right part is sorted
            else {
                // target in right part
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;
                // target in left part
                else
                    hi = mid - 1;
            }
        }
        
        return -1;
    }
};
