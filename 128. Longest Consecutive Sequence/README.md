# 128. Longest Consecutive Sequence

## 题目

题面：https://leetcode.com/problems/longest-consecutive-sequence/

对于给定的数，不考虑顺序关系，求出最长的连续元素子序列长度。子序列，可以不连续；子序列包含一串连续元素，而不是子序列中元素按给定的顺序连续。

## 思路

类似一个聚类的问题，相连续的数字是一类，问数量最多的那类中有几个独立元素。可以用 Union-Find 或者转化成 图的 DFS 遍历解决。但是，由于是连续数字这一简单的条件来维护同类（相连关系），可以简化解决。

### 1. 转化成图

对于像连续的数字，用无向边相连，对每个点进行DFS，求出最大的连通图节点数量。

``` c++
TC=O(N)，常数很大
SC=O(N)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        unordered_map<int, vector<int>> graph;
        for (int n : nums) {
            // 对于 n
            // n-1 存在，连接 n 到 n-1
            if (s.find(n-1) != s.end())
                graph[n].push_back(n-1);
            // n+1 存在，连接 n 到 n+1
            if (s.find(n+1) != s.end())
                graph[n].push_back(n+1);
        }
        
        
        int res = 0;
        // 访问过
        unordered_set<int> visited;
        // 对每个未访问过的点进行 DFS
        for (int n : nums) {
            if (visited.find(n) == visited.end()) {
                int tmp = 0;
                dfs(n, tmp, graph, visited);
                res = max(res, tmp);
            }
        }
        return res;
    }
    // DFS count 为本次搜索访问的点的数量
    void dfs(int cur, int& count, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
        count++;
        visited.insert(cur);
        for (int next : graph[cur]) {
            if (visited.find(next) == visited.end())
                dfs(next, count, graph, visited);
        }
    }
};
```

### 2. 简化

对于上述图中的某个连通分类，是一串连续的数字。利用哈希表保存所有元素，对于某个数字 n，若相邻的数字存在则继续搜索，若我们同时保证 n - 1 不在哈希表中，那么搜索方向只能是增大，简化实现，参考自题解。

``` c++
TC=O(N)
SC=O(N)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        
        int res = 0;
        for (int a : s) {
            // a 在集合中，a - 1 不在集合中，那么搜索方向只能是增大
            if (s.find(a-1) == s.end()) {
                // 搜索集合中连续的最大值
                int b = a + 1;
                while (s.find(b) != s.end())
                    b++;
                // 用 b - a 更新结果
                res = max(res, b - a);
            }
        }
        return res;
    }
};
```
