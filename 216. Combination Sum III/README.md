# 216. Combination Sum III

## 题目

题面：https://leetcode.com/problems/combination-sum-iii/

使用 1-9 的数字中的 k 个，组合得到目标和 n，每个数字只能用一次，求可能的组合个数。

## 实现

搜索回溯

``` c++
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> comb;
        search(k, n, 1, comb, res);
        return res;
    }
    
    void search(int k, int n, int cur, vector<int>& comb, vector<vector<int>>& res) {
        // 个数不足 或 目标不足
        if (n < 0 || k == 0) {
            // 目标达成
            if (n == 0)
                res.push_back(comb);
            return;
        }
        // 搜索
        for (int i = cur; i <= 10 - k; i++) {
            comb.push_back(i);
            // 用 i 及之后的元素 搜索 新目标和 n - i
            search(k - 1, n - i, i + 1, comb, res);
            // 回溯
            comb.pop_back();
        }
    }
};
```
