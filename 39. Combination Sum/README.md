# 39. Combination Sum

## 题目

题面：https://leetcode.com/problems/combination-sum/

一个不重复数组，组合出目标数 sum，元素可重复使用

## 实现

搜索回溯

``` c++
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> comb;
        search(target, 0, comb, res, candidates);
        return res;
    }
    
    void search(int target, int idx, vector<int>& comb, vector<vector<int>>& res, vector<int>& candidates) {
        // 剩余目标不足
        if (target <= 0) {
            // 达成目标
            if (target == 0)
                res.push_back(comb);
            return;
        }
        // 搜索
        for (int i = idx; i < candidates.size(); i++) {
            comb.push_back(candidates[i]);
            // 用包括元素 i 的数组（可重复）搜索新目标 target - cand[i]
            search(target - candidates[i], i, comb, res, candidates);
            // 回溯
            comb.pop_back();
        }
    }
};
```
