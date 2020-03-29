#include<math.h>
#include<iostream>

using namespace std;

/**
 * This is a bit level problem, make AND op within each int from [m, n]
 * BF is TLE
 * As long as one 0 exist in certain bit, the same bit in result will be 0
 * Also the operands are continuous, m and m+1 diff in right side (or not same at all)
 * The answer result is the common left side bit of m and n
*/

/**
 * First idea, take common bit from left (a.k.a MSB) one by one
 * three way to get MSB (most significant bit)
 *  1. (int)log2(num)
 *      Runtime: 12 ms, faster than 71.31%
 *  2. >> until zero
 *      Runtime: 12 ms, faster than 71.31%
 *  3. assembly code: bsrl
 *      Runtime: 4 ms, faster than 98.72%, (其实LC测得不太准)
 * Memory Usage: 6 MB, less than 100.00%
*/
class Solution1 {
public:
    int rangeBitwiseAnd(int m, int n) {
        int result = 0;
        
        int mb, nb;
        while (m != 0) {
            mb = getMSBV3(m);
            nb = getMSBV3(n);
            
            if (mb == nb) {
                // += also ok, but slow
                result |= mb;
                
                m -= mb;
                n -= nb;
            } 
            else {
                break;
            }   
        }
        return result;
    }
private:
    inline int getMSBV1(int num) {
        // 1. (int)log2(num)
        return 1 << (int)(log(num)/log(2));
    }
    
    inline int getMSBV2(int num) {
        // 2. >> until zero
        int msb = 0;
        while (num >>= 1)
            ++msb;
        return 1 << msb;
    }

    inline int getMSBV3(int num) {
        // 3. assembly code: bsrl
        int msb;
        __asm ("bsrl %1,%0" : "=r"(msb) : "r"(num));
        return 1 << msb;
    }
};



/**
 * Think from right
 * right shift until m == n
 * 
 * Runtime: 8 ms, faster than 90.54%
 * Memory Usage: 6 MB, less than 100.00%
*/
class Solution2 {
public:
    int rangeBitwiseAnd(int m, int n) {
        int right = 0;
        
        while (m != n) {
            ++right;
            // remove one bit
            m >>= 1;
            n >>= 1;
        }
        return m << right;
    }
};

/**
 * Also think from right
 *  n & (n - 1) make LSB zero
 * continue make LSB of n zero until n <= m, remaining is common left side
 *      m: b'11001, n: b'11101, remaining b'11000
 * 
 * Runtime: 8 ms, faster than 90.54%, (都不太准，4.8.16都有)
 * Memory Usage: 6.1 MB, less than 100.00%
*/
class Solution3 {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n) {
            // make LSB zero
            n &= n - 1;
        }
        return n;
    }
};
