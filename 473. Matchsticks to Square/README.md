# 473. Matchsticks to Square

## 题目

题面：https://leetcode.com/problems/matchsticks-to-square/

一堆长度不一的火柴，能不能拼成一个正方形，其实就是能不能被分成4份，每份和相等。

## 实现

## 1. DFS 回溯

认为要把火柴放入4个桶中，把每根火柴选择放入某个桶，记录每个桶火柴总长度，分配完后若每个长度相等就搜索到了。

两个优化：

* 若某个桶长度超过 1/4 总和，则剪枝提前中止
* 火柴降序排列，先分配长火柴，有助于剪枝

``` c++
TC=O(4^N)
SC=O(N)

class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        // 降序排序
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        // 求和
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        // 和必须整除 4
        if (sum % 4)
            return false;
        return search(0, matchsticks, 0, 0, 0, 0, sum / 4);
    }

    bool search(int idx, vector<int>& v, int l1, int l2, int l3, int l4, const int quarter) {
        // 分配完成，检查是否全相等
        if (idx == v.size()) {
            return l1 == l2 && l2 == l3 && l3 == l4;
        }
        // 剪枝，超过 1/4 sum 提前中止
        if (l1 > quarter || l2 > quarter || l3 > quarter || l4 > quarter) {
            return false;
        }
        // 4 桶搜索
        return search(idx + 1, v, l1+v[idx], l2, l3, l4, quarter)
            || search(idx + 1, v, l1, l2+v[idx], l3, l4, quarter)
            || search(idx + 1, v, l1, l2, l3+v[idx], l4, quarter)
            || search(idx + 1, v, l1, l2, l3, l4+v[idx], quarter);
    }
};
```

其实问题可以扩展到 K 个桶（即 [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)），用 vector 维护 K 个桶长度，而不是用 K 个变量，此处 K = 4。

``` c++
class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4)
            return false;
        // 4个桶
        vector<int> bucket(4);
        return search(0, matchsticks, bucket, sum / 4);
    }

    bool search(int idx, vector<int>& v, vector<int>& bucket, const int quarter) {
        if (idx == v.size()) {
            return bucket[0] == bucket[1] && bucket[1] == bucket[2] && bucket[2] == bucket[3];
        }
        // 4个桶搜索回溯
        for (int i = 0; i < 4; i++) {
            bucket[i] += v[idx];
            // 剪枝
            // 搜索 idx + 1
            if (bucket[i] <= quarter && search(idx + 1, v, bucket, quarter))
                return true;
            // 回溯
            bucket[i] -= v[idx];
        }
        return false;
    }
};
```

### 2. 状态压缩 DP

Reference: 
[火柴拼正方形,力扣官方题解](https://leetcode.cn/problems/matchsticks-to-square/solution/huo-chai-pin-zheng-fang-xing-by-leetcode-szdp/)

``` c++
TC=O(N*2^N)
SC=O(2^N)

class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        int totalLen = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (totalLen % 4 != 0) {
            return false;
        }
        int len = totalLen / 4, n = matchsticks.size();
        // 1<<N 种状态，表示 N个火柴选或不选
        // dp[i] 表示未被放满的边当前长度
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        // 遍历每种状态
        for (int s = 1; s < (1 << n); s++) {
            // 遍历每根火柴
            for (int k = 0; k < n; k++) {
                // 状态 s 的第 k 根火柴是选择的
                if ((s & (1 << k)) == 0) {
                    continue;
                }
                // s1 是第 k 根火柴不选择的状态
                int s1 = s & ~(1 << k);
                // s1 到 s 可行
                if (dp[s1] >= 0 && dp[s1] + matchsticks[k] <= len) {
                    dp[s] = (dp[s1] + matchsticks[k]) % len; // 若恰好放满，则放下一条边
                    break;
                }
            }
        }
        return dp[(1 << n) - 1] == 0;
    }
};
```
