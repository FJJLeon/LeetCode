#include<vector>

using namespace std;

/**
 * Sliding Window
 * mark sliding window [i, j]
 * for each j, find the smallest i so that the product of subarray[i,j] < k
 * 
 * Runtime: 128 ms, faster than 84.14%, O(N)
 * Memory Usage: 16.1 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1)
            return 0;
        int len = nums.size();
        int product = 1, count = 0;
        
        for (int i=0, j=0; j<len; ++j) {
            product *= nums[j];
            // control product of sliding window [i,j] (i may equal j) < k
            while (i <= j && product >= k) {
                product /= nums[i++];
            }
            count += j - i + 1;       
        }
        return count;
    }
};