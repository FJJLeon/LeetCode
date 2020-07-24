#include<vector>

using namespace std;

/**
 * bit manipulation
 * 
 * when only one number appears only once, we can find it just by xor all numbers
 * now there are two such number, marked as x, y
 * split all numbers into two group, xor all numbers in a group to find one
 * but how to split
 * we still utilize xor, xor all number -> get [twoXor] as xor of x and y
 * get a mask who only contains only one '1' and the bit exist in [twoXor]
 *      for the two special number, x & mask != y & mask
 *      for the other number, two same number must be split into the same group, after xor -> 0
 * 
 * LSB
 * Runtime: 16 ms, faster than 93.15%, O(2N) = O(N)
 * Memory Usage: 10.2 MB, less than 51.68%, O(1)
 * 
 * MSB
 * Runtime: 24 ms, faster than 42.09%, O(N), emm get LSB only need one &
 * Memory Usage: 10 MB, less than 93.27%, O(1)
 * 
*/
class Solution {
private:
    inline int MSBnum(int num) {
        // 3. assembly code: bsrl
        int msb;
        __asm ("bsrl %1,%0" : "=r"(msb) : "r"(num));
        return 1 << msb;
    }

    inline int LSBnum(int num) {
        return num & (-num);
    }
public:
    vector<int> singleNumber(vector<int>& nums) {
        // get the [xor] of the two number who appear only once, [marked as x, y]
        int twoXor = 0;
        for (int &n : nums)
            twoXor ^= n;
        // get a mask who only contains only one '1' and the bit exist in [twoXor]
        // here, LSB or MSB is ok
        int mask = LSBnum(twoXor);
        // use mask split all num into two group
        // for the two special number, x & mask != y & mask
        // because the only 1 comes from x^y, thus x and y are different in this bit
        // for the other number, two same number must be splited to the same group, after xor -> 0
        vector<int> res(2, 0);
        for (int n : nums) {
            if (n & mask)
                res[0] ^= n;
            else
                res[1] ^= n;
        }
        return res;
    }
};