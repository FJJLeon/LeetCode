# 399. Evaluate Division

## 题目

题面：https://leetcode.com/problems/evaluate-division/

给定一组除法等式，**Ai / Bi = Vi**，计算由此可以计算出查询除法等式 **Ci / Di**结果。

## 思路与实现

仍旧是图论题，BFS 从 **Ci** 进行搜索，记录累乘。

当然，可能不连通，此时返回 -1

``` c++

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int eqs = equations.size(), qys = queries.size();
        map<string_view, map<string_view, double>> g;
        for (int i = 0; i < eqs; i++) {
            string_view a = equations[i][0], b = equations[i][1];
            double v = values[i];
            g[a][b] = v;
            g[b][a] = 1/v;
        }
        int n = g.size();
        
        vector<double> res(qys, -1);
        for (int i = 0; i < qys; i++) {
            string_view c = queries[i][0], d = queries[i][1];
            if (g.find(c) == g.end() || g.find(d) == g.end())
                continue;
            
            map<string_view, bool> visit;
            queue<pair<string_view, double>> q;
            q.push({c, 1});
            visit[c] = true;
            while (!q.empty()) {
                auto& [cur, partDiv] = q.front(); q.pop();
                if (cur == d)
                    res[i] = partDiv;
                for (auto& [ngh, val] : g[cur]) {
                    if (!visit[ngh]) {
                        visit[ngh] = true;
                        q.push({ngh, partDiv * val});
                    }
                }
            }
        }
        
        return res;
    }
};
```