# [659. Split Array into Consecutive Subsequences](https://leetcode.com/problems/split-array-into-consecutive-subsequences/)

## 题面

判断能否把一个非降序数组划分为长度大于等于 3 的连续数组。类似把一副有顺序的牌分成长度大于等于 3 的顺子。

## 实现

### 0. 单 map 简单贪心模拟

一个比较暴力的实现是进行模拟，用一个 map 记录以某数字 n 结尾的各连续数组。遇到一个数组 x 时，我们需要判断是否粗在以 x - 1 结尾的数组：
* 若不存在，则需要新建以 x 结尾且长度为 1 的数组；
* 若存在，则可以添加到该数组后，但是这样的数组可能有多个，为了使每个数组都不小于 3，我们应选择长度最短的那个数组来延长。

选择长度最短的数组可以使用优先队列降低时间复杂度到 O(logN)，那么整体时间复杂度 O(NlogN)

``` c++
TC=O(NlogN)
SC=O(N)

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // 记录以某数结尾的各连续数组长度，按长度升序
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> StraightsEndWith;

        for (int num : nums) {
            // 不存在以 num - 1 的连续数组，需要新建 num 结尾的连续数组
            if (StraightsEndWith[num - 1].empty()) {
                StraightsEndWith[num].push(1);
            }
            // 存在以 num - 1 的连续数组，延长其中最短的那个
            else {
                int minLen = StraightsEndWith[num - 1].top(); StraightsEndWith[num - 1].pop();
                StraightsEndWith[num].push(minLen + 1);
            }
        }
        // 判断每个连续数组的长度是否都大于等于 3
        for (auto& [k, pq] : StraightsEndWith) {
            // 需要判断非空，实际上应该在 pop 空的时候 erase 比较好
            if (!pq.empty() && pq.top() < 3)
                return false;
        }
        return true;
    }
};
```

### 1. 贪心， 双 map

实际上，由于数组的非降序，我们在排顺子（长度大于等于 3 的连续数组）时，一旦发现某张牌既**不能添加到前面的顺子**中，也**不能和后面的牌形成（最短的）顺子**，那此时整副牌必然有单牌。

为了判断能否添加到前面的顺子，我们仍可以使用一个 map 记录以某数字 n 结尾的各连续数组，但此时只记录顺子的个数；如何能够只记录顺子呢，需要每次只生成顺子，同时也为了判断能否能和后面的牌形成（最短的）顺子，我们需要另一个 map 维护每张牌的剩余张数。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // 记录每张牌的剩余张数
        unordered_map<int, int> cnt;
        // 记录以某牌结尾的顺子个数
        unordered_map<int, int> cntStraightEndWith;
        for (int num : nums)
            cnt[num]++;
        for (int num : nums) {
            // 当前牌已经没有剩余，（和前面的牌形成了顺子）
            if (cnt[num] == 0)
                continue;
            // 当前牌张数减少 1
            cnt[num]--;
            // 当前牌可以添加到前面的顺子中
            if (cntStraightEndWith[num - 1] > 0) {
                cntStraightEndWith[num - 1]--;
                cntStraightEndWith[num]++;
            }
            // 当前牌可以和后面的牌形成长度为 3 的顺子
            else if (cnt[num + 1] > 0 && cnt[num + 2] > 0) {
                cnt[num + 1]--;
                cnt[num + 2]--;
                cntStraightEndWith[num + 2]++;
            }
            // 都不行
            else {
                return false;
            }
        }
        return true;
    }
};
```

### 3. 贪心 + 动态规划

逐步计算每中数字能形成的连续数组长度，只要区分长度为 1 2 和 大于等于 3 的，到达下一个数字时可以根据个数贪心得更新，若最后发现长度为 1 和 2 的数组还存在，则不行。当然，中间若发现数字不连续，这样其实是开启了一组新的计算。

* [【最优贪心解法】O(N) 时间 + O(1) 空间](https://leetcode.cn/problems/split-array-into-consecutive-subsequences/solution/tan-xin-o1-kong-jian-fu-za-du-de-zui-you-jie-fa-by/)
