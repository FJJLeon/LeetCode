#include<vector>

using namespace std;

/**
 * use mid check [lo, mi], (mi, hi] sorted or not
 * so as to find the min value
 * 
 * Runtime: 12 ms, faster than 72.83%, O(N)
 * Memory Usage: 12.3 MB, less than 62.32%， O(1)
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1, mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[hi]) { 
                lo = mid + 1;
            }
            else if (nums[mid] < nums[lo]) { 
                hi = mid;
                lo++;
            }
            else { // nums[lo] <= nums[mid] <= nums[hi] 
                hi--;
            }
        }
        
        return nums[lo];
    }
};