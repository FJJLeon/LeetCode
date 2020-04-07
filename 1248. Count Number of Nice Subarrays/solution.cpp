#include<vector>

using namespace std;

/**
 * Prefix Sum Idea
 * record prefix count of odd numbers
 *  vector is enough instead of unordered_map, max preOddCount = nums.size() is limited
 * 
 * Runtime: 172 ms, faster than 94.93%, O(N)
 * Memory Usage: 17.3 MB, less than 100.00%, O(N)
*/
class Solution1 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        //unordered_map<int, int> count({{0, 1}});
        vector<int> count(nums.size()+1, 0);
        count[0] = 1;
        int preOddCount = 0, res = 0;
        for (int n : nums) {
            if (n & 1)
                preOddCount++;
            if (preOddCount >= k)
                res += count[preOddCount - k];
            count[preOddCount]++;
        }
        return res;
    }
};

/**
 * Sliding Window [i, j]
 * use count recond even number between i and first odd num
 * 
 * Runtime: 168 ms, faster than 96.28%, O(N)
 * Memory Usage: 14.5 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int odd = 0, count = 0, len = nums.size();
        int res = 0;
        // sliding window [i, j]
        // use count recond even number between i and first odd num
        for (int i = 0, j = 0; j < len; ++j) {
            // new odd number found
            if (nums[j] & 1) {
                ++odd;
                count = 0;
            }
            // shrink window and record even number
            while (odd == k) {
                odd -= nums[i++] & 1;
                ++count;
            }
            // if no new odd number found, count will be added each time when j forward
            res += count;
        }
        return res;
    }
};
