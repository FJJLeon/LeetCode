

/**
 * 不会奇淫巧计,直接暴力算
*/
class Solution1 {
public:
    int findComplement(int num) {
        int res = 0, mask = 0;
        while (num != 0) {
            res += (1 - num & 1) << mask++;
            num >>= 1;
        }
        return res;
    }
};
/**
 * 关键在于利用 ^
 * 对于 num = 5 = 0b101, 使用 mask = 0b111，返回 num^mask = 0b010 即可
 * 所以问题在于找到与输入拥有相同最高位 1 的全 1 mask
 * 
 * 第一和第二钟类似，逐个 bit 判断并生成 mask，至多需要 31 次左移 和 32 次比较
 * 第三种方法，mask | (mask >> 1) 可以保证高位产生两个 1，依次倍增右移，需要 5 次右移 和 5 次或
*/
class Solution21 {
public:
    int findComplement(int num) {
        // 存在一个 overflow 的问题，若 num = INT_MAX = 2147483647 = 0x7fffffff
        // mask 若是 int， 则计算 mask 时会 overflow
        long mask = 1;
        while (mask <= num) {
            mask <<= 1;
        }
        return (mask - 1) ^ num;
    }
};
class Solution22 {
public:
    int findComplement(int num) {
        int mask = 1;
        while (mask < num) {
            mask = (mask << 1) + 1;
        }
        return mask ^ num;
    }
};
class Solution23 {
public:
    int findComplement(int num) {
        int mask = num;
        for (int i = 1; i <= 16; i *= 2) {
            mask |= mask >> i;
        }
        return mask ^ num;
    }
};
