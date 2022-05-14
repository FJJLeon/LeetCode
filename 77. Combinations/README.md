# 77. Combinations

## 题目

题面：https://leetcode.com/problems/combinations/

全组合，从 1 到 N 范围选择 K 个

## 实现

搜索回溯，N 个数，在搜索中选择元素并回溯

``` c++
TC=O(NCK*K)
SC=O(N)

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> comb;
        search(1, comb, res, n, k);
        return res;
    }
    
    void search(int idx, vector<int>& comb, vector<vector<int>>& res, int n, int k) {
        // 搜索到一个组合
        if (comb.size() == k) {
            res.push_back(comb);
            return;
        }
        // 循环选择
        for (int i = idx; i <= n; i++) {
            comb.push_back(i);
            search(i + 1, comb, res, n, k);
            // 回溯
            comb.pop_back();
        }
    }
};
```

当 idx 后的元素已经不足以获取 K 个元素时可以进行剪枝

``` c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> comb;
        search(1, comb, res, n, k);
        return res;
    }
    
    void search(int idx, vector<int>& comb, vector<vector<int>>& res, int n, int k) {
        if (comb.size() == k) {
            res.push_back(comb);
            return;
        }
        // 剪枝，可选元素不足
        for (int i = idx; i <= n - (k - comb.size()) + 1; i++) {
            comb.push_back(i);
            search(i + 1, comb, res, n, k);
            comb.pop_back();
        }
    }
};
```
