# 40. Combination Sum II

## 题目

题面：https://leetcode.com/problems/combination-sum-ii/

一个有重复数组，组合出目标数 sum，每个元素不可重复使用

## 实现

搜索回溯

``` c++
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // 排序可用数组，保证重复元素相邻
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> comb;
        search(target, 0, comb, res, candidates);
        return res;
    }
    
    void search(int target, int idx, vector<int>& comb, vector<vector<int>>& res, vector<int>& candidates) {
        // 剩余目标不足
        if (target <= 0) {
            // 目标达成
            if (target == 0)
                res.push_back(comb);
            return;
        }
        // 搜索
        for (int i = idx; i < candidates.size(); i++) {
            // 跳过重复元素
            if (i > idx && candidates[i] == candidates[i-1])
                continue;
            comb.push_back(candidates[i]);
            // 用元素 i+1 及之后的数组（不可重复）搜索新目标 target - cand[i]
            search(target - candidates[i], i + 1, comb, res, candidates);
            // 回溯
            comb.pop_back();
        }
    }
};
```
