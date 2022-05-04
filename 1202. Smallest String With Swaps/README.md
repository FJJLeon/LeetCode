# 1202. Smallest String With Swaps

## 题目

题面：https://leetcode.com/problems/smallest-string-with-swaps/

给定一组 pair，表示字符串 s 中的两个索引，每对 pair 中的两个索引可以任意次相互交换，问交换后所能得到的最小字典序新字符串。

## 思路与实现

朴素的想法，不断循环遍历每个可交换对 **pair = [a, b]**，若交换可以使索引小的字符变小（字典序在前），则交换，直到不存在这样的可交换对，就得到了最小字典序新字符串。

但是这样的贪心做法显然不优雅，昨天的题是MST，今天仍旧从图论角度考虑。认为
* 字符串的每个索引为点
* 每对可交换索引pair为边

这样形成一个无向图。字符可以在图中通过边移动，显然，只有**图中相连通的点代表的字符才能有交换的可能**。

那么，计算图中的连通分量(Connected Component, CC)，对每个连通分量内按字典序排序即可获取最小字典序字符串。

### 1. 邻接表+BFS求连通分量

* 输入的 pairs 边集转换为用邻接表表示的图
* 基于Queue对每个点BFS求连通分量
* 连通分量内字符串分离，字典序排序后重新映射回去

``` c++
TC=O(E + VlogV), 构建邻接表O(E)，BFS需要O(E+V)，排序最差需要O(VlogV)
SC=O(E + V)，存储邻接表需要O(E)，存储访问情况需要O(V)，BFS队列需要O(V)

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int vn = s.size(); // vertex size
        int en = pairs.size(); // edge size

        // 1. 构建邻接表，每对 pair 以无向边存储
        unordered_map<int, vector<int>> adj;
        for (auto& pair : pairs) {
            adj[pair[0]].push_back(pair[1]);
            adj[pair[1]].push_back(pair[0]);
        }
        // 标记点是否已访问过，即在某个CC中
        vector<bool> visited(vn, false);
        // 连通分量 组
        vector<vector<int>> ccs;
        // BFS 所需队列
        queue<int> q;
        // 2. 从每个顶点（索引）出发BFS计算连通分量
        for (int i = 0; i < vn; i++) {
            // 该点已访问过
            if (visited[i])
                continue;
            // 新连通分量
            vector<int> cc;
            // 当前点标记并入队
            visited[i] = true;
            cc.push_back(i);
            q.push(i);
            // BFS
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                // 将未访问过的与当前顶点相邻点入队，并标记
                // 这个标记一般在while中做，此处 testcase 会导致邻接表有相邻点重复，导致重复加入cc
                for (int ngh : adj[cur]) {
                    if (!visited[ngh]) {
                        visited[ngh] = true;
                        cc.push_back(ngh);
                        q.push(ngh);
                    }
                }
                
            }
            // 保存连通分量
            ccs.push_back(move(cc));
        }
        // 3. 对每个连通分量
        for (auto& cc : ccs) {
            // 连通分量索引排序，从小到大
            sort(cc.begin(), cc.end());
            // 分离连通分量对应的字符串
            string tmp;
            for (int i : cc)
                tmp += s[i];
            // 排序
            sort(tmp.begin(), tmp.end());
            // 将字典序排序后的字符串重新映射回去
            int j = 0;
            for (int i : cc)
                s[i] = tmp[j++];
        }
        
        return s;        
    }
};
```

### 2. DFS求连通分量

``` c++
TC=O(E+VlogV)，构建邻接表O(E)，DFS需要O(E+V)，排序最差需要O(VlogV)
SC=O(E+V)，存储邻接表需要O(E)，存储访问情况需要O(V)，DFS栈和递归变量各需要O(V)

class Solution {
public:
    // 邻接表，每对 pair 以无向边存储
    unordered_map<int, vector<int>> adj;
     // 标记点是否已访问过，即在某个CC中
    vector<bool> visited;
    
    // DFS 过程中保存访问到的字符 和 索引
    void DFS(string_view s, int cur, vector<int>& idx, vector<char>& str) {
        idx.push_back(cur);
        str.push_back(s[cur]);
        // 标记已访问
        visited[cur] = true;
        // 邻接点若没访问过，则递归DFS
        for (int next : adj[cur]) {
            if (!visited[next])
                DFS(s, next, idx, str);
        }
    }
    
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int vn = s.size(); // vertex size
        int en = pairs.size(); // edge size

        // 1. 构建邻接表，每对 pair 以无向边存储
        for (auto& pair : pairs) {
            adj[pair[0]].push_back(pair[1]);
            adj[pair[1]].push_back(pair[0]);
        }
        // 标记点是否已访问过，即在某个CC中
        visited.resize(vn, false);
        
        // 2. 从每个点开始DFS
        for (int i = 0; i < vn; i++) {
            if (visited[i])
                continue;
            // DFS
            vector<int> idx;
            vector<char> str;
            DFS(s, i, idx, str);
            // 排序
            sort(idx.begin(), idx.end());
            sort(str.begin(), str.end());
            // 重映射回去
            for (int i = 0; i < idx.size(); i++) {
                s[idx[i]] = str[i];
            }
        }
        
        return s;        
    }
};
```


### 3. 并查集求连通分量

利用并查集维护任意两点的连通性，最后提取同一连通分量的字符，进行排序

``` c++
TC=O(VlogV+Eα(E))，并查集单次合并需要O(α(E))，进行后续排序最差为一整个连通分量
SC=O(V)，并查集需要顶点数量V的空间

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
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int vn = s.size(); // vertex size
        int en = pairs.size(); // edge size

        // 合并可交换对
        UnionFind uf(vn);
        for (auto& pair : pairs) {
            uf.merge(pair[0], pair[1]);
        }
        // 提取各连通分量，注意此处得到的索引数组为升序
        unordered_map<int, vector<int>> ccs;
        for (int i = 0; i < vn; i++) {
            ccs[uf.find(i)].emplace_back(i);
        }

        for (auto& [g, cc] : ccs) {
            // 连通分量对应的索引数组已升序

            // 分离连通分量对应的字符串
            string tmp;
            for (int i : cc)
                tmp += s[i];
            // 排序
            sort(tmp.begin(), tmp.end());
            // 将字典序排序后的字符串重新映射回去
            int j = 0;
            for (int i : cc)
                s[i] = tmp[j++];
        }

        return s;
    }
};
```