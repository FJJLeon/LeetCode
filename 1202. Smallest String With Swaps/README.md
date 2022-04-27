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
TC=O(E + VlogV)
SC=O(E + V)

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int vn = s.size(); // vertex size
        int en = pairs.size(); // edge size

        // 邻接表，每对 pair 以无向边存储
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
        // 从每个顶点（索引）出发BFS计算连通分量
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
        // 对每个连通分量
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