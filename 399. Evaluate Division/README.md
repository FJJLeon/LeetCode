# 399. Evaluate Division

## 题目

题面：https://leetcode.com/problems/evaluate-division/

给定一组除法等式，**Ai / Bi = Vi**，由此可以计算出待查除法等式 **Ci / Di**结果。

## 思路与实现

仍旧考虑图论，对于等式 **Ai / Bi = Vi**，认为 **Ai** 和 **Bi** 为顶点，两点间有边，边权为 **Vi**。从 **Ci** 进行搜索，记录边权的累乘，若搜索到 **Di**，累乘结果即为 **Ci / Di** 值。

当然，两个待搜顶点可能不连通，此时返回 -1。

由于是一道查询题，潜在的优化是在计算查询过程中，将查询的除法等式计算结果加入邻接矩阵；更进一步，如果查询量很大，可以使用 [FLoyd算法](https://leetcode-cn.com/problems/evaluate-division/solution/chu-fa-qiu-zhi-by-leetcode-solution-8nxb/) 预计算出所有可能的等式结果，在查询时直接给出结果或不存在。

### 1. BFS

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
        // 除法结果，初始化为 -1
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

查看题解，可以发现上述 BFS 在编程实现上可优化的点包括：(1) 使用字符串表而不是直接用字符串作为键，即可不使用 map 来记录邻接矩阵和访问情况 (2) 访问情况数组同时可以用于记录除法结果，这样就不用将中间结果和顶点一起入队。

``` c++
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int eqs = equations.size(), qys = queries.size();

        int nvars = 0;
        // 字符串表
        unordered_map<string_view, int> variables;
        // 计数不同字符串个数，并添加到字符串表
        for (int i = 0; i < eqs; i++) {
            string_view a = equations[i][0], b = equations[i][1];
            if (variables.find(a) == variables.end()) {
                variables[a] = nvars++;
            }
            if (variables.find(b) == variables.end()) {
                variables[b] = nvars++;
            }
        }

        // 对于每个点，存储其直接连接到的所有点及对应的权值
        vector<vector<pair<int, double>>> adjs(nvars);
        for (int i = 0; i < eqs; i++) {
            // a -> b = v, b -> a = 1/v
            string_view a = equations[i][0], b = equations[i][1];
            int va = variables[a], vb = variables[b];
            double v = values[i];
            adjs[va].push_back({vb, v});
            adjs[vb].push_back({va, 1.0 / v});
        }
        // 除法结果，初始化为 -1
        vector<double> res(qys, -1);
        for (int i = 0; i < qys; i++) {
            // 待查等式 Ci / Di
            string_view c = queries[i][0], d = queries[i][1];
            // 若找不到，则直接跳过
            if (variables.find(c) == variables.end() || variables.find(d) == variables.end())
                continue;

            int vc = variables[c], vd = variables[d];
            if (vc == vd) {
                res[i] = 1.0;
            } else {
                // 标记，同时记录累乘结果
                vector<double> ratios(nvars, -1.0);
                // BFS 队列
                queue<int> q;
                // Ci 入队，标记初始值 1
                q.push(vc);
                ratios[vc] = 1.0;
                // BFS 搜索
                while (!q.empty() && ratios[vd] < 0) {
                    // 队列头顶点
                    int cur = q.front();
                    q.pop();
                    // 对未访问过的邻居顶点，入队
                    for (const auto [ngh, val]: adjs[cur]) {
                        if (ratios[ngh] < 0) {
                            ratios[ngh] = ratios[cur] * val;
                            q.push(ngh);
                        }
                    }
                }
                res[i] = ratios[vd];
            }
        }
        return res;
    }
};
```

### 2. DFS

``` c++
class Solution {
private:
    void dfs(int vc, int vd, const vector<vector<pair<int, double>>>& adjs, vector<double>& ratios) {
        // 已搜索到，返回
        if (ratios[vd] > 0)
            return;
        // 对邻居DFS
        for (const auto [ngh, val] : adjs[vc]) {
            if (ratios[ngh] < 0) {
                ratios[ngh] = ratios[vc] * val;
                dfs(ngh, vd, adjs, ratios);
            }
        }
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int eqs = equations.size(), qys = queries.size();

        int nvars = 0;
        // 字符串表
        unordered_map<string_view, int> variables;
        // 计数不同字符串个数，并添加到字符串表
        for (int i = 0; i < eqs; i++) {
            string_view a = equations[i][0], b = equations[i][1];
            if (variables.find(a) == variables.end()) {
                variables[a] = nvars++;
            }
            if (variables.find(b) == variables.end()) {
                variables[b] = nvars++;
            }
        }

        // 对于每个点，存储其直接连接到的所有点及对应的权值
        vector<vector<pair<int, double>>> adjs(nvars);
        for (int i = 0; i < eqs; i++) {
            // a -> b = v, b -> a = 1/v
            string_view a = equations[i][0], b = equations[i][1];
            int va = variables[a], vb = variables[b];
            double v = values[i];
            adjs[va].push_back({vb, v});
            adjs[vb].push_back({va, 1.0 / v});
        }
        // 除法结果，初始化为 -1
        vector<double> res(qys, -1);
        for (int i = 0; i < qys; i++) {
            // 待查等式 Ci / Di
            string_view c = queries[i][0], d = queries[i][1];
            // 若找不到，则直接跳过
            if (variables.find(c) == variables.end() || variables.find(d) == variables.end())
                continue;

            int vc = variables[c], vd = variables[d];
            if (vc == vd) {
                res[i] = 1.0;
            } else {
                // 标记，同时记录累乘结果
                vector<double> ratios(nvars, -1.0);
                ratios[vc] = 1.0;
                // DFS 搜索
                dfs(vc, vd, adjs, ratios);
                res[i] = ratios[vd];
            }
        }
        return res;
    }
};
```

### 3. 带权并查集

在并查集的合并和查询过程中，额外维护了一个元素与代表元素(group,father)间的权重比值，从而可以计算任意两个同组元素的比值即等式结果。

https://leetcode-cn.com/problems/evaluate-division/solution/chu-fa-qiu-zhi-by-leetcode-solution-8nxb/