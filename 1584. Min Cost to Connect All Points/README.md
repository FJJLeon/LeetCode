# 1584. Min Cost to Connect All Points

## 题目

题面：https://leetcode.com/problems/min-cost-to-connect-all-points/

给定二维X-Y坐标系上一组点，要使得所有点连通，求最小 cost，连接两个点的 **cost** 为两点间的曼哈顿距离即街区距离。

## 思路与实现

可以认为这是一个完全图，每两个点间都有边，边权为两点的曼哈顿距离，求图中的最小生成树MST。图中有N个点，则MST中有 N-1 条边，求解**MST**一般有**Prim**和**Kruskal**算法。

### 1. Prim using PriorityQueue

所有点集为V，逐渐扩大T，使用优先队列 PQ 获取 T 和 V-T 的最小权重割边 e，割边 e 在 V-T 中的点加入 T。

``` c++
TC=O(N^2 logN)
SC=O(N^2)，最差情况下会把完全图的所有边都压入优先队列

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
        // trick，从 0-0 边压入pq，边权为 0
        pq.push({0, 0});
        // 判断N个点是否已经加入 T
        vector<bool> connected(n, false);
        // 最小 cost
        int res = 0;
        for (int c = 0; c < n; c++) {
            // 若优先队列中目前最小权不是割边，则 pop
            while (connected[pq.top().second]) {
                pq.pop();
            }
            // cutEdge T / V-T 最小权重割边 e
            edge cutEdge = pq.top(); pq.pop();
            int cur = cutEdge.second;
            // 最小MST cost 更新
            res += mhdis(cutEdge, points);
            // 标记 e 在 V-T 中的点已在 T 中
            connected[cur] = true;
            // 将 T / V-T 的边加入 PQ
            for (int i = 0; i < n; i++) {
                if (!connected[i])
                    pq.push({cur, i});
            }
        }
        
        return res;
    }
    // 边的曼哈顿记录
    inline int mhdis(edge& e, vector<vector<int>>& points) {
        point& n1 = points[e.first], &n2 = points[e.second];
        return abs(n1[0] - n2[0]) + abs(n1[1] - n2[1]);
    }
};


```
