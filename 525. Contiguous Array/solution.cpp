#include<unordered_map>
#include<vector>

using namespace std;

/**
 * like prefix sum, use variable count initialized to 0, +1 when encounter one and -1 when encounter zero
 * when count change while traverse nums, if same value of count appear at different index of nums i,j, the subarray[i,j] is valid
 * 
 * Runtime: 144 ms, 53.38 %, O(N)
 * Memory Usage: 17.5 MB, O(N)
*/
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxlen = 0, count = 0;
        // map key: count, value: first appear index
        unordered_map<int, int> first;
        for (int i = 0; i < nums.size(); ++i) {
            count += nums[i] == 1 ? 1 : -1;
            // zero means subarray from beginning is valid
            if (count == 0) {
                maxlen = i + 1;
                continue;
            }
            // find first appear index
            auto it = first.find(count);
            if (it != first.end())
                maxlen = max(maxlen, i - it->second);
            else
                first[count] = i;
        }
        
        return maxlen;
    }
};
