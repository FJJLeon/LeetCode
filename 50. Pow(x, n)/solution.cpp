

/**
 * x^2n = (x^n)^2
 * i for digit in binary of n, multiply corresponding x^(2^i) for each one bit in i index (from low to high)
 * 
 * Runtime: 0 ms, faster than 100.00%, O(logN)
 * Memory Usage: 6 MB, less than 62.29%, O(1)
*/
class Solution {
public:
    double myPow(double x, int n) {
        // cast for corner case, n = -2^31, -n cannot be represented as integer
        long cast_n = n;
        if (cast_n < 0) {
            x = 1/x;
            cast_n = -cast_n;
        }
        double res = 1;
        double multiplier = x;
        // multiply corresponding x^(2^i)
        while (cast_n) {
            if (cast_n & 1)
                res *= multiplier;
            multiplier *= multiplier;
            cast_n >>= 1;
        }
        return res;
    }
};
