#include<vector>
#include<limits.h>

using namespace std;

/**
 * Kadane's Algorithm, like DP
 * maxSubSum at each ending is based on maxSubSum at previous ending
 * https://zh.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E5%AD%90%E6%95%B0%E5%88%97%E9%97%AE%E9%A2%98
 * 
 * Runtime: 4 ms, O(N)
 * Memory Usage: 6.9 MB, O(1)
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN, sum = 0;
        for (int n : nums) {
            // calculate maxSubSum at this ending
            sum = max(sum + n, n);
            
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
};


/**
 * Divide-and-Conquer
 * maxSubSum locate at left subarray or right subarray or cross left-right subarray
 * 
 * Runtime: 12 ms, O(NlogN)
 * Memory Usage: 7.2 MB, O(logN) for recurive stack
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return maxLRSub(nums, 0, nums.size()-1);
    }
private:
    int maxLRSub(vector<int>& nums, int left, int right) {
        // recursive exit
        if (left == right) {
            return nums[left];
        }
        // mid elem index
        int center = (left + right) / 2;
        
        // recursive solve subSum of left subarray
        int leftMax = maxLRSub(nums, left, center);
        // recursive solve subSum of right subarray
        int rightMax = maxLRSub(nums, center + 1, right);
        
        // solve subSum cross left-right subarray
        // solve borden max sub end at mid
        int leftBordenMax = INT_MIN;
        int leftBorden = 0;
        for (int i=center; i>=left; --i) {
            leftBorden += nums[i];
            leftBordenMax = max(leftBordenMax, leftBorden);
        }
        // solve borden max sub begin at mid
        int rightBordenMax = INT_MIN;
        int rightBorden = 0;
        for (int i=center+1; i<=right; ++i) {
            rightBorden += nums[i];
            rightBordenMax = max(rightBordenMax, rightBorden);
        }
        // add up cross maxSubSum
        int crossMax = leftBordenMax + rightBordenMax;

        return max(max(leftMax, rightMax), crossMax);
    }
};
