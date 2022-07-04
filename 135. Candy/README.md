# 135. Candy

## 题目

题面：https://leetcode-cn.com/problems/candy/

给定每个孩子的优先级，每个孩子至少一个糖果，如果某个孩子比两侧孩子的优先级高，则要起码比两侧的孩子中大的那个多一个糖果，问最少需要发多少糖果。

## 思路与实现

这题贪心的思路不难想，对于每个山谷孩子，只需要给一个糖果，从山谷向两侧爬升，每步多给一个糖果即可。对于山峰孩子，则需要给取从两侧爬升中较大数量的糖果（即山峰认为是在一个更长的爬升序列中），主要是如何优雅得实现这个贪心的过程。

### 1. 1~2 Pass

自个想的实现，看了题解后就觉得不优雅。

很直接，从左向右遍历，对于上升序列，我们只要依次给递增数量的糖果即可；

对于下降序列，我们记录这一状态，我们在进入下降序列时记录山峰位置，然后在进入下一个上升或持平数对的时候，发现之前是存在下降状态的，那么就可以根据记录的山峰位置和当前可知的山谷位置反向爬升，并依次递增给糖果。

注意，对于山峰需要给两侧较长序列的糖果值；对于末尾的下降序列也要补充反向爬升。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n < 2)
            return n;
        
        // 记录每个孩子的糖果数量
        vector<int> candy(n);
        // 第一个孩子先给一个糖果，若后续发现他是一个山峰，则会在反向爬升时修改
        candy[0] = 1;
        // 记录前一个孩子的糖果值
        int prev = ratings[0];
        // 记录是否在下降序列
        bool down = false;
        // 记录上一个山峰位置
        int peak;

        // lambda 函数实现反向爬升
        auto reverseClimb = [&candy](int valley, int peak) {
            int inc = 1;
            // 从 valley 到 peak + 1，依次给递增数量的糖果
            for (int j = valley; j > peak; j--) {
                candy[j] = inc++;
            }
            // peak 给两侧较长序列的糖果值
            candy[peak] = max(candy[peak], candy[peak+1] + 1);
        };

        // 从左向右遍历
        for (int i = 1; i < n; i++) {
            int cur = ratings[i];
            // 对于上升或持平序列
            if (cur >= prev) {
                // 发现之前是存在下降状态未处理的
                if (down) {
                    down = false;
                    // 从 i-1 到 peak 反向爬升
                    reverseClimb(i - 1, peak);
                }
                // 当前孩子给糖果，上升序列递增给，持平暂时只需给一个
                candy[i] = (cur > prev) ? candy[i-1] + 1 : 1;
            }
            // 下降序列
            else {
                // 第一次进入该下降序列，记录山峰位置
                if (down == false) {
                    peak = i - 1;
                    down = true;
                }
            }
            // 更新 prev
            prev = cur;
        }
        // 除了可能的末尾下降序列
        if (down) {
            reverseClimb(n - 1, peak);
        }
        // 求和
        int res = accumulate(candy.begin(), candy.end(), 0);
        return res;
    }
};
```

这是一个 1~2 Pass，对于下降序列会反向爬升增加访问次数，最差情况下若整个序列都为下降序列则会需要 2 Pass。把下降序列的反向爬升处理延迟放到了发现紧接着的上升数对的时候，还需要一个可能的末尾下降序列额外处理，实现逻辑较为复杂，且不优雅。
