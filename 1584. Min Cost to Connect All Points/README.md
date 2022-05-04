# 1584. Min Cost to Connect All Points

## 题目

题面：https://leetcode.com/problems/min-cost-to-connect-all-points/

给定二维X-Y坐标系上一组点，要使得所有点连通，求最小 cost，连接两个点的 **cost** 为两点间的曼哈顿距离即街区距离 (|xi - xj| + |yi - yj|)。

## 思路与实现

可以认为这是一个完全图，每两个点间都有边，边权为两点的曼哈顿距离，求图中的最小生成树MST。图中有N个点，则MST中有 N-1 条边，求解**MST**一般有**Prim**和**Kruskal**算法。

### 1. Prim using PriorityQueue

Prim算法：所有点集为V，逐渐将点加入 T。使用优先队列 PQ 获取 T 和 V-T 的最小权重割边 e，割边 e 在 V-T 中的点加入 T。

``` c++
TC=O(n^2log(n))，基于堆优化的Prim一般 TC=O(Elog(V))，这里 E=V^2
SC=O(n^2)，最差情况下会把完全图的所有边都压入优先队列

using edge = pair<int, int>;
using point = vector<int>;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        // lambda 表达式比较器 用于 优先队列
        // 需要捕获points数组和对象指针
        auto cmp = [&points, this](edge& e1, edge& e2) {
            return mhdis(e1, points) > mhdis(e2, points);
        };
        priority_queue<edge, vector<edge>, decltype(cmp)> pq(cmp);
        // trick，将 0-0 虚拟自环边压入pq，边权为 0
        pq.push({0, 0});
        // 判断N个点是否已经加入 T
        vector<bool> connected(n, false);
        // 最小 cost
        int res = 0;
        for (int c = 0; c < n; c++) {
            // 若优先队列中目前最小权边不是割边，即该边两顶点都在T中，则 pop
            while (connected[pq.top().second]) {
                pq.pop();
            }
            // cutEdge T / V-T 最小权重割边 e
            edge cutEdge = pq.top(); pq.pop();
            int cur = cutEdge.second;
            // 最小MST cost 更新
            res += mhdis(cutEdge, points);
            // 将 e 在 V-T 中的点加入 T，标记之
            connected[cur] = true;
            // 将新加入 T 的 cur 顶点到 V-T 的边加入 PQ
            for (int i = 0; i < n; i++) {
                if (!connected[i])
                    pq.push({cur, i});
            }
        }
        
        return res;
    }
    // 边的曼哈顿距离
    inline int mhdis(edge& e, vector<vector<int>>& points) {
        point& n1 = points[e.first], &n2 = points[e.second];
        return abs(n1[0] - n2[0]) + abs(n1[1] - n2[1]);
    }
};
```

以上实现的优先队列比较器每次比较时都要进行距离计算，而队列中保存的是边的两个顶点。然而，实际上当一条边进入优先队列后，只有在 V-T 集合中的那个顶点才有意义。因此，可以进行编码上的优化。

``` c++
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        // lambda 表达式，[&] 引用传递捕获表达式所在范围的局部变量
        auto dist = [&](int i, int j) -> int {
            return abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        };
        // {边权, to顶点}，比较时按 first 升序
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // 0,0 虚拟自环边
        pq.push({0, 0});
        // 判断N个点是否已经加入 T
        vector<bool> connected(n, false);
         // 最小 cost
        int res = 0;
        for (int c = 0; c < n; c++) {
            // 若优先队列中目前最小权边不是割边，即该边两顶点都在T中，则 pop
            while (connected[pq.top().second]) {
                pq.pop();
            }
            // 最小权割边的距离，V-T 中的顶点
            auto [weight, cur] = pq.top(); pq.pop();
            // 最小MST cost 更新
            res += weight;
            // 将 e 在 V-T 中的点加入 T，标记之
            connected[cur] = true;
            // 将新加入 T 的 cur 顶点到 V-T 的边加入 PQ
            for (int i = 0; i < n; i++) {
                if (!connected[i])
                    pq.push({dist(cur, i), i});
            }
        }
        
        return res;
    }
};
```

本题中的图为完全图，不使用堆，而直接使用数组维护所有点到 T 中点的距离，每次寻找下一条最小权割边时都确定需要遍历所有顶点，这样的时间复杂度为**Θ(V^2)=Θ(n^2)**。而使用堆优化的Prim时间复杂度为**O(ElogV) = O(n^2log(n))**，只能说最差情况下堆优化的可能反而比直接用数组维护差。


### 2. Kruskal using UnionFind

Kruskal 算法：按权值从小到大选择边，如果这样的边不会在 T 中形成环，则作为 MST 的一部分加入到 T 中，否则不加入。
那么如何检测选择的边是否会在 T 中形成环，使用并查集(DisjointSetUnion, UnionFind)。如果新选择边的两个顶点在 T 中即是**连通**的，那么加入该边就会形成环，使用并查集可以方便得完成这一目标。

``` c++
TC=O(n^2log(n)), Kruskal算法时间复杂度在于对边的排序与并查集操作，一般TC=O(ElogE)，本题 E=n^2，n为输入点数
SC=O(n^2), 边集数组O(n^2)，并查集O(n)

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

    bool merge(int x, int y) {
        int gx = find(x), gy = find(y);
        // 若两者属于同一组别，则已连通
        if (gx == gy) {
            return false;
        }
        // 按秩合并
        if (rank[gx] < rank[gy]) {
            swap(gx, gy);
        }
        // 保证小秩合并到大秩
        rank[gx] += rank[gy];
        group[gy] = gx;
        
        return true;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        // 生成边数组，{曼哈顿距离, 点i，点j}
        vector<array<int, 3>> edges;
        // lambda 表达式，[&] 引用传递捕获表达式所在范围的局部变量
        auto dist = [&](int i, int j) -> int {
            return abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        };
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                edges.emplace_back(array<int, 3>{dist(i, j), i, j});
            }
        }
        // 按距离从小到大排序
        sort(edges.begin(), edges.end(), 
            [](array<int, 3> e1, array<int, 3> e2) -> bool {return e1[0] < e2[0];});

        UnionFind uf(n);
        int res = 0, visited = 0;
        for (auto& [dist, i, j] : edges) {
            // 不连通则合并
            if (uf.merge(i, j)) {
                // 累加合并边权 - 距离
                res += dist;
                // 已加入 T 的顶点数
                visited++;
                if (visited == n) {
                    break;
                }
            }
        }

        return res;
    }
};
```

### Reference:
1. [【详解】并查集](https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/solution/tu-jie-bing-cha-ji-by-yexiso-nbcz/)
2. [连接所有点的最小费用](https://leetcode-cn.com/problems/min-cost-to-connect-all-points/solution/lian-jie-suo-you-dian-de-zui-xiao-fei-yo-kcx7/)