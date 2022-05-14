# 743. Network Delay Time

## 题目

题面：https://leetcode.com/problems/network-delay-time/

1-N节点图，带权有向边，计算从 k 节点到所有其他节点的最短路径，即单源最短路径。

## 实现

Dijkstra 算法

``` c++
TC=O(V+ElogV)
SC=O(V+E)

using pii = pair<int, int>;
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // src -> [{delay, dest}]
        vector<vector<pii>> adjList(n + 1, vector<pii>());
        // 构建邻接表
        for (auto& edge : times) {
            adjList[edge[0]].push_back({edge[2], edge[1]});
        }
        // 保存节点 k 到其他节点的距离
        vector<int> dist(n+1, INT_MAX);
        // {delay, dest}
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, k});
        dist[k] = 0;

        while (!pq.empty()) {
            // K 到当前节点的距离
            auto [curDelay, cur] = pq.top(); pq.pop();
            if (curDelay > dist[cur])
                continue;
            // 遍历当前节点的邻居
            for (auto& [ngbDelay, ngb] : adjList[cur]) {
                // 更新距离并入队
                if (dist[ngb] > curDelay + ngbDelay) {
                    dist[ngb] = curDelay + ngbDelay;
                    pq.push({dist[ngb], ngb});
                }
            }
        }
        
        int res = INT_MIN;
        // 计算 K 到 [1-n] 其他节点的距离的最大值
        for (int i = 1; i <= n; i++) {
            res = max(res, dist[i]);
        }
        // 若有不可达节点，则返回 -1，否则即返回距离最大值
        return res == INT_MAX ? -1 : res;
    }
};
```