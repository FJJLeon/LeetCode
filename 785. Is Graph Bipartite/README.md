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
                    // 已着色，检查是否不同色
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

### 2. DFS

``` c++
TC=O(V+E)
SC=O(V)

class Solution {
private:
    // 染色数组。-1 : 未着色，0 : 红，1 : 蓝
    vector<int> color;
public:
    // 期望以 curColor 对 cur 顶点进行染色
    bool DFS(int cur, int curColor, const vector<vector<int>>& graph) {
        // cur 顶点已染色，检查是否满足期望
        if (color[cur] != -1) {
            return color[cur] == curColor;
        }
        // 未染色，则以 curColor 进行染色
        color[cur] = curColor;
        // 并期望将所有邻居顶点染成另一种颜色
        int nghColor = curColor ^ 1;
        for (int ngh : graph[cur]) {
            if (!DFS(ngh, nghColor, graph))
                return false;
        }
        
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        
        color.resize(n, -1);
        // 对每个未染色顶点进行 DFS
        for (int i = 0; i < n; i++) {
            if (color[i] == -1 && !DFS(i, 0, graph)) {
                return false;
            }
        }
        
        return true;
    }
};
```

### 3. 并查集

遍历每个顶点，利用并查集合并每个顶点的所有邻居顶点，并判断是否存在邻居顶点和当前顶点处于同一集合，若存在，即不能二分。

``` c++
TC=O(V+E)
SC=O(V)
class UnionFind {
private:
    // 第i个元素所属的组别(parent,represent)
    vector<int> group;
    // 秩，可表征该组别深度，用于优化合并
    vector<int> rank;
public:
    UnionFind(int n) {
        group = vector<int>(n);
        rank = vector<int>(n, 1);
        for (int i = 0; i < n; i++) {
            group[i] = i;
        }
    }

    int find(int x) {
        // 路径压缩，在查询过程中缩短路径
        if (group[x] != x) {
            group[x] = find(group[x]);
        }
        return group[x];
    }

    int isConnected(int x, int y) {
        return find(x) == find(y);
    }
    
    void merge(int x, int y) {
        int gx = find(x), gy = find(y);
        // 若两者属于同一组别，则无需合并
        if (gx == gy) {
            return;
        }
        // 按秩合并
        if (rank[gx] < rank[gy]) {
            swap(gx, gy);
        }
        // 保证小秩组合并到大秩组
        rank[gx] += rank[gy];
        group[gy] = gx;
    }
};

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        UnionFind uf(n);
        // 对每个顶点，合并所有邻接顶点
        for (int i = 0; i < n; i++) {
            const vector<int>& adj = graph[i];
            for (int j : adj) {
                // 检查当前顶点和所有邻居顶点是否在同一集合，若在则不能二分
                if (uf.isConnected(i, j))
                    return false;
                // 合并邻居顶点到第一个邻居
                uf.merge(adj[0], j);
            }
        }
        
        return true;
    }
};
```
