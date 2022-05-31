# 29. Divide Two Integers

## 题目

题面：https://leetcode.com/problems/divide-two-integers/

不用乘除取余操作计算两数相除

## 实现

用左移操作计算，被除数最多比除数左移多少次后还大，然后减去最大值重复计算。

```
dividend = 17 = (10001)  divisor = 3 = (11)   res = 0
17 - (3 << 2) = 17 - 12 = 5 >= 0,   res += 1 << 2, res = 4, remain dividend = 5
5 - (3 << 0) = 2 >= 0, res += 1 << 0, res = 5, remain dividend = 2
2 < 3, break

res = 5
```

``` c++
TC=O(logN)
SC=O(1)

class Solution {
public:
    int divide(int dividend, int divisor) {
        // corner case
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        long a = abs(dividend), b = abs(divisor), res = 0;
        bool sign = (dividend > 0) == (divisor > 0);
        
        while  (a >= b) {
            int shift = 0;
            while (a - (b << shift << 1) >= 0) {
                shift++;
            }
            res += 1 << shift;
            a -= b << shift;
        }
        return sign ? res : -res;
    }
};
```
