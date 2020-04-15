#include<vector>

using namespace std;

/**
 * store prefix and suffix product of each index
 * 
 * Runtime: 40 ms, faster than 75.23%, O(N)
 * Memory Usage: 10.8 MB, less than 100.00%, O(N)
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> output(len);
        
        vector<int> prefix(len, 1), suffix(len, 1);
        // store prefix product, prefix[i] = product[0, 1, .., i-1] = prefix[i-1] * nums[i-1]
        for (int i = 1; i < len; ++i) 
            prefix[i] = prefix[i-1] * nums[i-1];
        // store suffix product, suffix[i] = product[i+1, i+2, .., len-1] = nums[i+1] * suffix[i+1]
        for (int i = len - 2; i >= 0; --i)
            suffix[i] = suffix[i+1] * nums[i+1];
        // output[i] = product[0, 1, .., i-1, i+1, i+2, .., len-2, len-1] = prefix[i] * suffix[i]
        for (int i = 0; i < len; ++i)
            output[i] = prefix[i] * suffix[i];
        
        return output;
    }
};

/**
 * reuse output space, make O(1) space
 * 
 * Runtime: 32 ms, faster than 99.87%, O(N)
 * Memory Usage: 10.3 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> output(len, 1);
        
        // store prefix product, prefix[i] = product[0, 1, .., i-1] = prefix[i-1] * nums[i-1]
        for (int i = 1; i < len; ++i) 
            output[i] = output[i-1] * nums[i-1];
        // simply use a variable record suffix when traverse back
        int suffix = 1;
        for (int i = len - 1; i >= 0; --i) {
            output[i] *= suffix;
            suffix *= nums[i];
        }
        return output;
    }
};
