#include<vector>

using namespace std;

/**
 * binary search, pigeonhole principle(鸽巢原理)
 * for the n + 1 numbers with value among [1, n], there must be a number who occur twice
 * duplicate number must be one of 1 to n, binary search the number
 * given the number [mid], count the occurence of number <= [mid]
 *      if count <= mid, the duplicate is among [mid + 1, n]
 *      if count > mid,  the duplicate is among [1, mid - 1]
 * 
 * Runtime: 20 ms, faster than 50.38%, O(N*logN)
 * Memory Usage: 11.2 MB, less than 34.07%, O(1)
*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int lo = 1, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int count = 0;
            for (int n : nums)
                if (n <= mid)
                    ++count;
            if (count <= mid)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return lo;
    }
};