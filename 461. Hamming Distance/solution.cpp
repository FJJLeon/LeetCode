

/**
 * get hamming distance: count of different bits for two integer x and y
 * t = x xor y, count all ones in t's binary representation
 *      use t & (t-1) remove the right-most one, count all one's
 * 
 * Runtime: 0 ms, faster than 100.00%
 * Memory Usage: 5.9 MB, less than 67.28%
*/
class Solution {
public:
    int hammingDistance(int x, int y) {
        int t = x ^ y;
        int res = 0;
        while (t) {
            // t&(t-1) remove right-most one
            t &= t - 1;
            ++res;
        }
        return res;
    }
};
