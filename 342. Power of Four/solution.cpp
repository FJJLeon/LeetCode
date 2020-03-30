

/**
 * assmbly code: bsrl get MSB
 * 
 * Runtime: 0 ms, faster than 100.00%
 * Memory Usage: 5.8 MB, less than 100.00%
*/
class Solution1 {
public:
    bool isPowerOfFour(int num) {
        int msb;
        __asm ("bsrl %1,%0" : "=r"(msb) : "r"(num));
        return msb % 2 == 0 && num - (1 << msb) == 0;
    }
};

/**
 * bit manipulation
 * 
 * Runtime: 0 ms, faster than 100.00%
 * Memory Usage: 6 MB, less than 100.00%
*/
class Solution2 {
public:
    bool isPowerOfFour(int num) {
        return num > 0  // pow4 greater than zero
            && (num & (num - 1)) == 0   // x&(x-1) remove LSB, only one 1
            && (num & 0x55555555) != 0; // the only one 1 locate at even bit
    }
};