#include<vector>
#include<math.h>

using namespace std;

/**
 * count the number of occurrences for each num
 * 
 * Runtime: 116 ms, faster than 61.35%,O(N)
 * Memory Usage: 13.9 MB, less than 100.00%,O(N)
*/
class Solution1 {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        vector<int> v(len+1, 0);
        for (int n : nums) {
            v[n]++;
        }
        vector<int> res;
        for (int i=1; i<len+1; ++i) {
            if (v[i] == 0)
                res.push_back(i);
        }
        return res;
    }
};


/**
 * make use of the fact that the N length array only contain the numbers between [1, N]
 * 
 * there are several tricks:
 * a. for each position i, mark the value of index **nums[i]-1** as negative in first loop, and then check those positive
 * Runtime: 120 ms, faster than 40.54%
 * Memory Usage: 12.6 MB, less than 100.00%
 * 
 * b. for each position i, add N to the value of index **nums[i]%N-1** in first loop, and then check less then or equal to N
 * Runtime: 116 ms, faster than 61.35%
 * Memory Usage: 12.6 MB, less than 100.00% 
 * 
 * the problem is the input array modified
 * 
*/
class Solution2a {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i=0; i<nums.size(); ++i) {
            int index = abs(nums[i]) - 1;
            if (nums[index] > 0)
                nums[index] = -nums[index];
        }
        vector<int> res;
        for (int i=0; i<nums.size(); ++i) {
            if (nums[i] > 0)
                res.push_back(i+1);
        }
        return res;
    }
};

class Solution2b {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int N = nums.size();
        for (int a : nums) {
            nums[(a - 1) % N] += N;
        }
        vector<int> res;
        for (int i=0; i<nums.size(); ++i) {
            if (nums[i] <= N)
                res.push_back(i+1);
        }
        return res;
    }
};
