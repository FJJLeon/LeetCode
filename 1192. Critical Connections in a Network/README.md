# 1192. Critical Connections in a Network

## 题目

题面：https://leetcode.com/problems/critical-connections-in-a-network/

0 到 n-1 共计 n 个服务器通过无向连接连通，只有一个连通分量。若移除某个连接，则会使得某几个服务器之间无法连通，找到所有这样的连接。

用图论来说，这样的连接叫做“桥”，一条边是桥当且仅当这条边不在任何环上。

## Tarjan 实现

使用 Tarjan 算法找桥。Tarjan 算法能解决强连通分量、双连通分量、割点和桥、最近公共祖先等问题。

基本思想是在DFS过程中找环。如何确定环呢，需要记录每个节点的访问顺序，若DFS发现一个邻居N已经在更早时候被访问过，那么说明除了当前这条边以外，还有一条路径可以从邻居到达当前点，当前边便不是桥。同时维护一个深搜的搜索树能访问到的所有节点的最小遍历到时间，用于回溯时判断桥。

将在一个同一个环上的点标记成一个相同的数字（Tarjan认为是一个自增的访问时间）。在DFS回溯的时候，若发现邻居点的标记比自己要大（要晚），说明邻居节点无论如何无法通过其他路径到达当前节点，那么当前节点和这个邻居节点不在一个环上，只有这条边连通，因此这条边是一座桥。

``` c++
TC=O(E)
SC=O(V)=O(N)

class Solution {
public:
    vector<vector<int>> adj;
    // dfn-节点被DFS遍历到的时间，按访问顺序增大
    // low-节点及之后的深搜能访问到的所有节点的最小遍历到时间，若出现环则对同一节点会出现 low < dfn
    vector<int> dfn, low;
    int time = 1;
    vector<vector<int>> res;
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        adj = vector<vector<int>>(n, vector<int>());
        dfn.resize(n, -1);
        low.resize(n);
        // 邻接表
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        // 用 tarjan 算法 DFS 遍历
        tarjan(0, -1);
        return res;
    }
    
    void tarjan(int cur, int father) {
        dfn[cur] = low[cur] = time++; // 初始化 cur 被访问的时间
        for (int ngb : adj[cur]) {
            if (ngb == father) // 跳过父亲节点
                continue;
            else if (dfn[ngb] == -1) { // 未遍历过的邻居，DFS
                tarjan(ngb, cur);
                low[cur] = min(low[cur], low[ngb]); // 若邻居及之后深搜发现环，low[ngb] 会变小，则同样需要更新 low[cur]
                if (dfn[cur] < low[ngb]) // 若 cur 被访问的时间 小于 邻居ngb 能深搜到的所有顶点访问时间，说明 cur 和 ngb 不在一个环上，除了当前这条边没有其他路径可以连通，则 cur-ngb 是桥即Critical Connections
                    res.push_back(vector<int>{cur, ngb});
            }
            else { // dfn 已经设置过，遇到了DFS更早遍历过的点，说明出现了环（ngb 从当前深搜路径到达能到达 cur，而现在 ngb 又是 cur 的直接邻居），更新 low[cur]
                low[cur] = min(low[cur], dfn[ngb]); 
            }
        }
    }
};
```

## Reference
* [Leetcode 1192. Critical Connections in a Network 查找集群内的「关键连接」- 终结解析+Java代码](https://www.bilibili.com/video/BV15t4y197eq/)
* [60 分钟搞定图论中的 Tarjan 算法（一）](https://zhuanlan.zhihu.com/p/101923309)