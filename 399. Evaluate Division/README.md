# 399. Evaluate Division

## 题目

题面：https://leetcode.com/problems/evaluate-division/

给定一组除法等式，**Ai / Bi = Vi**，由此可以计算出待查除法等式 **Ci / Di**结果。

## 思路与实现

仍旧考虑图论，对于等式 **Ai / Bi = Vi**，认为 **Ai** 和 **Bi** 为顶点，两点间有边，边权为 **Vi**。从 **Ci** 进行搜索，记录边权的累乘，若搜索到 **Di**，累乘结果即为 **Ci / Di** 值。

当然，两个待搜顶点可能不连通，此时返回 -1。

``` c++

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int eqs = equations.size(), qys = queries.size();
        // 嵌套 map 的图表示，类似邻接矩阵
        map<string_view, map<string_view, double>> g;
        for (int i = 0; i < eqs; i++) {
            // a -> b = v, b -> a = 1/v
            string_view a = equations[i][0], b = equations[i][1];
            double v = values[i];
            g[a][b] = v;
            g[b][a] = 1/v;
        }
        int n = g.size();
        // 除法结果
        vector<double> res(qys, -1);
        // 对每个查询结果
        for (int i = 0; i < qys; i++) {
            // 待查等式 Ci / Di
            string_view c = queries[i][0], d = queries[i][1];
            // 若找不到，则直接跳过
            if (g.find(c) == g.end() || g.find(d) == g.end())
                continue;
            // 标记是否已经访问过
            map<string_view, bool> visit;
            // BFS 队列，保存 {顶点, 路径累乘}
            queue<pair<string_view, double>> q;
            // {Ci, 1} 入队，标记已访问
            q.push({c, 1});
            visit[c] = true;
            // BFS 搜索
            while (!q.empty()) {
                // 队列头顶点，路径乘积
                auto& [cur, partDiv] = q.front(); q.pop();
                // 搜索到 Di
                if (cur == d) {
                    res[i] = partDiv;
                    break;
                }
                // 对未访问过的邻居顶点，入队
                for (auto& [ngh, val] : g[cur]) {
                    if (!visit[ngh]) {
                        // 标记已访问
                        visit[ngh] = true;
                        // {邻居顶点，新的路径累积} 入队
                        q.push({ngh, partDiv * val});
                    }
                }
            }
        }
        
        return res;
    }
};
```