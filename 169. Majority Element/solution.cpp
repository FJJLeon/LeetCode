#include<vector>
#include<unordered_map>

using namespace std;

/**
 * Hash Map
 * 
 * Runtime: 20 ms, 80.44%
 * Memory Usage: 10.3 MB, 100.00%
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        int len = nums.size();
        for (int el : nums) {
            if (++count[el] > len/2)
                return el;
        }
        // won't reach
        return -1;
    }
};