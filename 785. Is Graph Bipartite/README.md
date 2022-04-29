# 785. Is Graph Bipartite?

## 题目

题面：https://leetcode.com/problems/is-graph-bipartite/

给定一个邻接表表示的图，判断是不是二分图，即图中的顶点可以被分成两个集合，所有的边都是两个集合间的，而集合的顶点间没有边。

## 思路与实现

判断是不是二分图，BFS 着色，在BFS过程中将相邻顶点标记为两种不同的颜色，如果发现相邻已经被标记过的点颜色相同，则无法二分；若能完成BFS着色，则可以完成。

### 1. 迭代BFS + 二着色

``` c++
TC=O(V+E)
SC=O(V)

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // -1 : 未着色，0 : 红，1 : 蓝
        vector<int> color(n, -1);
        // 迭代用 BFS 队列
        queue<int> q;
        // 对每个顶点 BFS，可能存在非连通情况
        for (int i = 0; i < n; i++) {
            // 已经检查过 
            if (color[i] != -1) {
                continue;
            }
            // 初始着色
            int curColor = 0;
            // 着色第一个顶点
            q.push(i);
            color[i] = curColor;
            // BFS
            while(!q.empty()) {
                int cur = q.front(); q.pop();
                // 给邻接顶点着反色 同时检查是否矛盾
                curColor = color[cur] ^ 1;
                for (int ngh : graph[cur]) {
                    // 未着色，给邻居顶点着反色，并进行 BFS
                    if (color[ngh] == -1) {
                        color[ngh] = curColor;
                        q.push(ngh);
                    }
                    // 已着色，检查是否反色
                    else {
                        if (color[ngh] != curColor) {
                            return false;
                        }
                    }
                }
            }
        }
        // 能二着色完全图，可以二分
        return true;
    }
};
```