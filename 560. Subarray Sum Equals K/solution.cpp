#include<vector>
#include<unordered_map>

using namespace std;

/**
 * Prefix Sum
 * 
 * Runtime: 56 ms, faster than 52.11%, O(N)
 * Memory Usage: 15.5 MB, less than 30.67%, O(N)
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // key : prefix sum, value : occurrence of the prefix sum
        unordered_map<int, int> prefixSum;
        prefixSum[0] = 1;
        int sum = 0, count = 0;
        for (auto n : nums) {
            sum += n;
            count += prefixSum[sum - k]; // this operation should before next, or a empty subarray will be counted as valid if k = 0
            ++prefixSum[sum];
        }
        return count;
    }
};
