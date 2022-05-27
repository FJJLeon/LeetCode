# 191. Number of 1 Bits

## 题目

题面：https://leetcode.com/problems/number-of-1-bits/

32位数，二进制表示中，计算 1 的个数

## 实现

暴力做法就循环 32 次，每个位置看看是不是 1，统计一遍，对任意输入稳定操作 32 次。

### 1. n & (n - 1)

位操作中，**n&(n-1)** 可以去除最后一位 1。

n-1 实际上是把 leftmost 的 1 去掉，并在右边全填上 1，这与原数进行与运算就消除了该 leftmost 1，保持其他不变。如 $n=(10110100)_2, n\&(n-1) = (10110100)_2 \& (10110011)_2 = (10110000)_2$。

操作次数为输入数中 1 的个数

``` c++
TC=O(1)
SC=O(1)
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while (n) {
            n &= n - 1;
            count++;
        }
        return count;
    }
};
```

### 2. follow up

能想到的就只到上面那个了，以下奇淫巧计来自题解讨论

* 当查询数量很大时，可以进行缓存，最极端的就是把 32 位整数所有结果都存下来。但是这样占用空间很大，做一个权衡，只保存一个 8 位宽的查询表，分段查询。

``` C++
class Solution {
public:
    // 8 位宽的查询表
    unsigned char lookup[256];
    // 实例化时初始化查询表
    Solution() {
        memset(lookup, 0, sizeof(lookup));
        for (int i = 0; i < 256; i++){
            lookup[i] = (i & 1) + lookup[i / 2];
        }
    }
    int hammingWeight(uint32_t n) {
        return lookup[n & 0xff] + lookup[(n >> 8) & 0xff] + 
            lookup[(n >> 16) & 0xff] + lookup[(n >> 24) & 0xff];
    }
};
```

* 宏计算的静态查询表

``` C++
class Solution {
public:
    static const unsigned char lookup[256];
    
    int hammingWeight(uint32_t n) {
        return lookup[n & 0xff] + lookup[(n >> 8) & 0xff] + 
            lookup[(n >> 16) & 0xff] + lookup[(n >> 24) & 0xff];
    }
};

const unsigned char Solution::lookup[256] = 
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};
```

* 分块逐步扩展加

逐次用 0x55555555、0x33333333、0x0f0f0f0f、0x00ff00ff、0x0000ffff 分块计算，依次把每2位、4位、8位、16位、32位中的'1'个数计算出来。

对应的二进制表示为
```
0x55555555 = 01010101 01010101 01010101 01010101
0x33333333 = 00110011 00110011 00110011 00110011
0x0F0F0F0F = 00001111 00001111 00001111 00001111
0x00FF00FF = 00000000 11111111 00000000 11111111
0x0000FFFF = 00000000 00000000 11111111 11111111
```

以操作 4 位宽为例，如 $(1101)_2$，只要操作两次就得到结果，32 位宽需要 5 次。

```
0x55: 1101 & 0101 + X110 & 0101 = 0101 + 0100 = 1001
1001 表示 1101 第一个 2位 中有 2 个 '1'，第二个 2位 中有 1 个 '1'
0x33: 1001 & 0011 + XX10 & 0011 = 0001 + 0010 = 0011
0011 表示 1101 第一个 4位 中有 3 个 '1'
```

``` c++
class Solution {
public:    
    int hammingWeight(uint32_t n) {
        n = (n & (0x55555555)) + ((n >> 1) & (0x55555555));
        n = (n & (0x33333333)) + ((n >> 2) & (0x33333333));
        n = (n & (0x0f0f0f0f)) + ((n >> 4) & (0x0f0f0f0f));
        n = (n & (0x00ff00ff)) + ((n >> 8) & (0x00ff00ff));
        n = (n & (0x0000ffff)) + ((n >> 16) & (0x0000ffff));
        
        return n;
    }
};
```

Reference

* [[Python] n & (n-1) trick + even faster, explained](https://leetcode.com/problems/number-of-1-bits/discuss/1044775/Python-n-and-(n-1)-trick-%2B-even-faster-explained)
* [Bit Twiddling Hacks, from Stanford](http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive)

