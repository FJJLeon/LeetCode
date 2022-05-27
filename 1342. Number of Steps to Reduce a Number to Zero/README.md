# 1342. Number of Steps to Reduce a Number to Zero

## 题目

题面： https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/

每次操作，对于偶数除以2，对于奇数减1。

## 实现

奇偶判断只和二进制表示中最右边的位有关

* 偶数，最右位为 0，除以2等价于右移1位，操作一次；
* 奇数，最右位为 1，减1之后最右位变成0。若整个数还不是0，一定是偶数，需要右移一位，接着去操作下一位。即最右位为 1 时需要操作两次。若整个数是0，即操作的是 leftmost 1，则操作结束。

``` c++
class Solution {
public:
    int numberOfSteps(int num) {
        if (num == 0)
            return 0;
        int shift = 0, ones = 0;
        while (num) {
            if (num & 1)
                ones++;
            num >>= 1;
            shift++;
        }
        return shift + ones - 1;
    }
};
```
简单点就是
``` c++
class Solution {
public:
    int numberOfSteps(int num) {
        if (num == 0)
            return 0;
        int res = 0;
        while (num) {
            res += (num & 1) ? 2 : 1;
            num >>= 1;
        }
        return res - 1;
    }
};
```
实际上这是在计算 leftmost 1 到最右侧的距离，和二进制表示中 1 的个数，只要知道这俩就可以直接算。有 build_in 函数可以直接得到。

* __builtin_clz 获取二进制表示下前导 0 的个数
* __builtin_popcount 获取二进制表示下 1 的个数

``` c++
class Solution {
public:
    int numberOfSteps (int num) {
        return num ? 31 - __builtin_clz(num) + __builtin_popcount(num) : 0;
    }
};
```
