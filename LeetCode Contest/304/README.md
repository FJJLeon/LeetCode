# 周赛 304

20220731

## T1. 使数组中所有元素都等于零

https://leetcode.cn/problems/make-array-zero-by-subtracting-equal-amounts/

非负整数数组，每次选择大于 0 的最小数，减去之，重复操作使数组中所有元素都等于零，问最少操作次数。

实际是在求数组去重后正数的个数。

### 1. 模拟

做的时候就没想到去重，甚至还用优先队列去模拟，就算模拟其实也只要开头排序一次即可。

``` c++
TC=O(NlogN)

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> pq, tmppq;
        for (int num : nums) {
            if (num != 0)
                pq.push(num);
        }
        
        int res = 0;
        while (!pq.empty()) {
            int sub = pq.top(); pq.pop();
            for (int s = pq.size(); s > 0; s--) {
                int tmp = pq.top() - sub; pq.pop();
                if (tmp > 0)
                    tmppq.push(tmp);
            }
            pq.swap(tmppq);
            res++;
        }
        return res;
    }
};
```

### 2. set 去重

``` c++
TC=O(N)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        set<int> s(nums.begin(), nums.end());
        s.erase(0);
        return s.size();
    }
};
```

## T2. 分组的最大数量

https://leetcode.cn/problems/maximum-number-of-groups-entering-a-competition/

脑筋急转弯，分组内的总分没有意义，升序排序后，按照顺序分配给 1、2 ~ k 大小的分组，必然满足条件。因此只要求分组的最大数量即可，每组大小是 1 ~ k。

1 ~ k 求和直到再加就超过 grades.size()，返回此时 k 值。

``` c++
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int len = 1, n = grades.size();
        while (n >= len) {
            n -= len;
            len++;
        }
        return len - 1;
    }
};
```

等差数列求和公式来求根 (1+k)k/2 = n

``` c++
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        return (-1 + sqrt(1+8*grades.size())) / 2;
    }
};
```

## T3. 找到离给定两个节点最近的节点

https://leetcode.cn/problems/find-closest-node-to-given-two-nodes/

N点N边，每个点至多只有一条出边，为内向基环树，两个点的能到达的公共点中，某个点能使得这两个距离中较大值最小，返回该点。若有多个则返回编号小的那个。

由于每个点最多只有一条出边，可以直接深度遍历两个点，分别记录能到达的所有点，或者陷入基环中。对于两者能到达的公共点，求距离较大值最小的点的编号。

距离可以使用 vector(n) 维护，也可以使用 map 记录，但是不能仅使用 set 来判断是否出现重复点。若只是用 set，不维护距离，则需要对两者是否在环中，是否能相遇，是否在环外的同一条路径等等条件进行分类讨论，甚是麻烦。

``` c++
TC=O(N)

class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        // lambda 函数 DFS
        auto dfs = [&](int cur) -> vector<int> {
            vector<int> dis(n, -1);
            int clock = 0;
            // 到达终点或发现环
            while (cur != -1 && dis[cur] == -1) {
                dis[cur] = clock++;
                cur = edges[cur];
            }
            return dis;
        };
        vector<int> dis1 = dfs(node1), dis2 = dfs(node2);
        // 对于公共点，求距离较大值最小的点的编号
        int minDis = n, res = -1;
        for (int i = 0; i < n; i++) {
            if (dis1[i] == -1 || dis2[i] == -1)
                continue;
            int d = max(dis1[i], dis2[i]);
            // 按照 0 ~ n-1 遍历，所以只要小于
            if (d < minDis) {
                minDis = d;
                res = i;
            }
        }
        return res;
    }
};
```

以上解法直观得说是两个点分别前进，直到到达终点或发现环，同时记录能到达点的距离，最后对所有节点进行比较。

另一种做法是从两个点同时出发前进，两者每次前进一步，分别用一个 set 记录访问到的点，若两个 set 第一次出现交集，则该点就是希望的结果公共点。

``` c++
TC=O(N)

class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        unordered_set<int> s1, s2;
        int n1 = node1, n2 = node2;
        // s1 保存 n1 出发路径点，s2 保存 n2 出发路径点
        // n1 n2 中尚有一个能前进
        while ((n1 != -1 && s1.find(n1) == s1.end()) || (n2 != -1 && s2.find(n2) == s2.end())) {
            // 若 n1 n2 直接相遇，则就返回相遇节点编号
            // 即两条相同长度的分支交汇
            if (n1 == n2)
                return n1;
            // 若发现集合有交集，则返回交集点，若同时两个都互相交集，返回编号小的那个
            if (s1.find(n2) != s1.end() && s2.find(n1) != s2.end())
                return min(n1, n2);
            if (s1.find(n2) != s1.end())
                return n2;
            if (s2.find(n1) != s2.end())
                return n1;
            // n1 n2 前进一步
            if (n1 != -1) {
                s1.insert(n1);
                n1 = edges[n1];
            }
            if (n2 != -1) {
                s2.insert(n2);
                n2 = edges[n2];
            }
        }

        return -1;
    }
};
```

## T4. 图中的最长环

https://leetcode.cn/problems/longest-cycle-in-a-graph/

同样是基环树，但题设不保证连通，故实际上是个基环森林，可以有多个环。

从每个点进行DFS，用 set 记录访问点，判断是否有环出现，当出现环时对环再进行一次遍历，获取环的长度。对于不同点的 DFS，当发现在之前的 DFS 中已经访问过，则无需继续遍历。

``` c++
TC=O(N)

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        // 全局已访问点
        set<int> allVisit;
        int n = edges.size(), path, res = -1;
        for (int i = 0; i < n; i++) {
            // 入口点已经访问过
            if (allVisit.find(i) != allVisit.end())
                continue;
            int cur = i;
            // 局部DFS已访问点
            set<int> curVisit;
            // 路径长度
            path = 0;
            // 到达终点或发现环
            while (cur != -1 && curVisit.find(cur) == curVisit.end()) {
                // DFS 过程中发现全局已访问过，则跳出
                if (allVisit.find(cur) != allVisit.end())
                    break;
                curVisit.insert(cur);
                cur = edges[cur];
                path++;
            }
            // 全局访问过，无需计算
            if (allVisit.find(cur) != allVisit.end())
                continue;
            // 发现新环
            if (cur != -1) {
                // 新环入口 即为起始点
                if (cur == i) 
                    res = max(res, path);
                // 重新遍历访问新环，获取环长度
                else {
                    set<int> tmp;
                    path = 0;
                    while (cur != -1 && tmp.find(cur) == tmp.end()) {
                        tmp.insert(cur);
                        cur = edges[cur];
                        path++;
                    }
                    res = max(res, path);
                }
            }
            // 局部已访问点添加到全局已访问点
            allVisit.insert(curVisit.begin(), curVisit.end());
        }
        return res;
    }
};
```

也可以在 DFS 过程中使用 map 或者 vector 维护路径长度，避免再进行一次环遍历。

``` c++
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> dis(n, -1);
        // clock 全局访问时间
        int clock = 1, res = -1;
        for (int i = 0; i < n; i++) {
            // 入口点已经访问过
            if (dis[i] != -1)
                continue;
            // 记录此次 DFS 开始时的时间
            int cur = i, start_clock = clock;
            // DFS 到终点或发现环 或发现已经全局访问过
            while (cur != -1 && dis[cur] == -1) {
                dis[cur] = clock++;
                cur = edges[cur];
            }
            // cur 不是开路，且访问时间小于等于本次 DFS 开始时的时间，则说明发现一个新环
            if (cur != -1 && dis[cur] >= start_clock)
                res = max(res, clock - dis[cur]);
        }
        return res;
    }
};
```
