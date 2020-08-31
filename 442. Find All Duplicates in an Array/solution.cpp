#include<vector>

using namespace std;

/**
 * array hash map
 * 
 * Runtime: 112 ms, faster than 92.92%, O(N)
 * Memory Usage: 33.9 MB, less than 40.18%, O(N)
*/
class Solution1 {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        vector<bool> appear(n+1, false);
        vector<int> res;
        for (int e : nums) {
            if (!appear[e]) {
                appear[e] = true;
            }
            else {
                res.push_back(e);
            }
        }
        return res;
    }
};


/**
 * self hash
 * use negative index as appeared
 * 
 * Runtime: 120 ms, faster than 78.32%, O(N)
 * Memory Usage: 33.6 MB, less than 77.95%, O(1)
*/
class Solution2 {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int e : nums) {
            if (nums[abs(e) - 1] < 0) {
                res.push_back(abs(e));
            }
            nums[abs(e) - 1] *= -1;
        }
        return res;
    }
};