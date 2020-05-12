#include<vector>

using namespace std;

/**
 * binary search
 * a pair begin with odd index will be same if left half is all paired
 * find first even-index number followed by different number
 *      0 1 2 3 4 5 6 7 8
 *      1 1 2 3 3 4 4 5 5
 * 
 * Runtime: 16 ms, faster than 29.23%, O(logN)
 * Memory Usage: 11.2 MB, less than 7.14%, O(1)
*/
class Solution1 {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];
        int lo = 0, hi = nums.size() - 1, mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            // make mid be odd index
            if (mid & 1)
                --mid;
            // if paired, goto right half
            if (nums[mid] == nums[mid+1])
                lo = mid+2;
            else
                hi = mid-1;
        }
        return nums[lo];
    }
};

/**
 * lo & hi is not regular index, but pair index
 * no need to be bothered by odd and even index
 * come from @leetcode.com/penghuan
 * 
 * Runtime: 16 ms, faster than 29.23%
 * Memory Usage: 11.1 MB, less than 7.14%
*/
class Solution2 {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int len = nums.size();
        // pair index
        int lo = 0, hi = len / 2, mid;
        // binary search pair index
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (nums[2*mid] == nums[2*mid + 1])
                lo = mid + 1;
            else 
                hi = mid;
        }
        return nums[2*lo];
    }
};