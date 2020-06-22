#include<vector>

using namespace std;

/**
 * bit operation
 * for each bit of each num, add together and mod by 3 get the bit value of the single number
 * 
 * Runtime: 12 ms, faster than 93.19%, O(N)
 * Memory Usage: 9.6 MB, less than 51.27%, O(32) = O(1) still extra memory
*/
class Solution1 {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> digits(32, 0);
        
        for (int n : nums) {
            for (int i = 0; i < 32 && n != 0; ++i) {
                digits[i] += (n & 1);
                n >>= 1;
            }
        }
        
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            res += (digits[i] % 3) << i;
        }
        return res;
    }
};