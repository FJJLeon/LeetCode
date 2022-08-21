# 双周赛 85

20220820

## [T1.得到 K 个黑块的最少涂色次数](https://leetcode.cn/problems/minimum-recolors-to-get-k-consecutive-black-blocks/)

只包含黑白的一维块，想要获取长度为 k 的黑块，可以把白块涂黑，问最少的涂黑操作

### 滑动窗口

``` c++
TC=O(N)
SC=O(1)

class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();
        int l = 0, r = 0, cntW = 0;
        // 形成 k 长窗口
        while (r < k) {
            if (blocks[r] == 'W')
                cntW++;
            r++;
        }
        int res = cntW;
        // 窗口滑动
        while (r < n) {
            if (blocks[r++] == 'W')
                cntW++;
            if (blocks[l++] == 'W')
                cntW--;
            res = min(res, cntW);
        }
        return res;
    }
};
```

## [T2.6157. 二进制字符串重新安排顺序需要的时间](https://leetcode.cn/problems/time-needed-to-rearrange-a-binary-string/)

只有 01 的二进制字符串，一时间同时将所有 01 替换为 10，直到没有 01，问需要多少时间

其实最后就是把所有的 1 都移到左侧，只想到暴力的 O(N^2) 做法

### 暴力

``` c++
TC=O(N^2) 无法证明

class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        bool exist;
        int seconds = 0, n = s.size();
        do {
            int i = 0;
            exist = false;
            while (i < n) {
                if (s[i] == '0' && s[i + 1] == '1') {
                    s[i] = '1';
                    s[i+1] = '0';
                    i += 2;
                    exist = true;
                }
                else {
                    i++;
                }
            }
            if (exist)
                seconds++;
        } while (exist);
        return seconds;
    }
};
```

### O(N) 一轮遍历

对于每个 1，要移到对应位置需要的操作次数容易计算，但是若该 1 左侧还有一个 1，那么必须要等待且只需要等待一时间才能移动

Reference: [O(n) 一次遍历](https://leetcode.cn/problems/time-needed-to-rearrange-a-binary-string/solution/by-endlesscheng-pq2x/)

## [T3.6158. 字母移位 II](https://leetcode.cn/problems/shifting-letters-ii/)

[848. 字母移位](https://leetcode.cn/problems/shifting-letters/) 升级版。

848 移动的区间是 0-i，因此可以用前缀和，而这里是 shifts[i][0] - shifts[i][1]，需要的是区间加法。

这里只需要区间加法完成最后进行一次单点查询，不需要线段树(适合多次查询)，差分数组即可。

|  | 区间更新 | 查询 |
| - | - | -|
|差分数组| O(1) | O(N) |
|线段树| O(logN) | O(logN) |

``` c++
TC=O(N+M)
SC=O(N)

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int> diff(n, 0);
        for (auto& sf : shifts) {
            int inc = (sf[2] == 1) ? 1 : -1;
            // 差分数组，对于区间 [l, r], diff[l]++, diff[r-1]--
            diff[sf[0]] += inc;
            // 更好的做法是数组开大一个
            if (sf[1] + 1 < n)
                diff[sf[1] + 1] -= inc;
        }
        // 差分数组求和得到 每个单点值
        for (int i = 1; i < n; i++) {
            diff[i] += diff[i-1];
        }
        // 对于每个字母，进行环形移位操作
        for (int i = 0; i < n; i++) {
            // 取余，计算到 'a' 的距离
            int idx = (s[i] - 'a' + diff[i]) % 26;
            // 防止负数
            idx = (idx + 26) % 26;
            s[i] = 'a' + idx;
        }
        return s;
    }
};
```

Reference：[线段树解法](https://leetcode.cn/problems/shifting-letters-ii/solution/by-lfool-vbqw/)


## [T4.6159. 删除操作后的最大子段和](https://leetcode.cn/problems/maximum-segment-sum-after-removals/)

对于给定数组，依次删除查询位置的数，并在查询中的索引位置割开，问割开后形成的几个子数组中最大的数组和。所有数最后都会被恰好删除。

正向进行删除模拟没有好的思路，最后也是结束了才写出来，而逆推使用并查集的思路好很多。

### 1. 正向模拟，前缀和 + 优先队列 + set

首先计算前缀和，便于后面计算区间和。

对于每次割裂，若割的位置在当前的最大和所在区间，则最大和会发生变化；若不在最大和所在区间，则此时最大和不变，可以直接记录该最大和。

但是割裂的操作需要记录，当后续最大和区间被割裂时，第二大区间和可能在之前的割裂中已经不存在，需要在此时进行割裂。

综上，使用优先队列记录 区间及对应的区间和，根据区间和降序排列。并使用集合缓存还未进行的割裂操作，当需要割裂时，若发现集合中有割裂位置在队列头区间（当前最大和对应区间）内，则需要继续割裂，直到不存在。

对于如何发现是否有缓存割裂点在头区间内，使用 set 的 lower_bound 操作可以降低时间复杂度到 O(logN)

``` c++
TC=O(NlogN)
SC=O(N)

class Solution {
public:
    using a3 = array<long long, 3>;
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        int n = nums.size();
        // 前缀和，大小+1，避免 0 边界
        vector<long long> prefix(n + 1);
        for (int i = 1; i <= n; i++) {
            prefix[i] = prefix[i-1] + nums[i - 1];
        }
        // 优先队列记录，[区间和，左边界，右边界]，以区间和为关键字（array）
        priority_queue<a3> pq;
        // 最大区间入队
        pq.push({prefix[n], 1, n});
        // 割裂操作的缓存集合
        set<int> rmCache;
        vector<long long> res(n);
        for (int i = 0; i < n; i++) {
            // 当前割裂操作，+1 与前缀和统一
            int rm = removeQueries[i] + 1;
            rmCache.insert(rm);
            // 当前最大区间和
            auto curMax = pq.top();
            int l = curMax[1], r = curMax[2];
            // 找到第一个大于等于左边界的割裂点
            auto it = rmCache.lower_bound(l);
            // 若割裂点存在且在该区间内部，则进行割裂操作
            while (it != rmCache.end() && *it <= r) {
                rm = *it;
                rmCache.erase(it);
                
                pq.pop();
                // 左区间入队
                if (rm - 1 >= l)
                    pq.push({prefix[rm - 1] - prefix[l - 1], l, rm - 1});
                // 右区间入队
                if (r >= rm + 1)
                    pq.push({prefix[r] - prefix[rm], rm + 1, r});
                // 继续判断下一个头区间
                curMax = pq.top();
                l = curMax[1], r = curMax[2];
                it = rmCache.lower_bound(l);
            }
            // 若队列空，则已经删除完
            if (pq.empty())
                continue;
            
            res[i] = curMax[0];
        }
        return res;
    }
};
```

看到的正向模拟实现：

使用 set 记录当前已经删除的割裂点，对于下一个割裂点 p ，用 upper_bound 找到第一个比 p 大的已删除点 R，以及最后一个比 p 小的已删除点 L (= prev(R))，割裂区间 [L, R]。

在记录区间和时，存在重复，需要记录数量，用 map<rangeSum, count> 或者 multiset

Reference: [模拟](https://leetcode.cn/problems/maximum-segment-sum-after-removals/solution/by-tsreaper-a4y0/)

### 2. 反向添加，并查集

割裂难以实现，而倒着做进行区间合并则可以用并查集，高效合并两个子段。

注意添加 x 时进行 x 到 fa[x+1] 的合并，此时 x+1 可能是被删除的，故求的和是只加了 nums[x]

Reference:[倒序回答 + 并查集](https://leetcode.cn/problems/maximum-segment-sum-after-removals/solution/by-endlesscheng-p61j/)
