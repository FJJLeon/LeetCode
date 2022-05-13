# 46. Permutations

## 题目

题面：https://leetcode.com/problems/permutations/

全排列，无重复元素

## 思路与实现

### 1. 基于标记数组的回溯

N个空位，从左往右选择数组元素填入。使用一个标记数组判断是否使用过。

``` c++
TC=O(N*N!)
SC=O(N)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        // 标记数组元素是否使用过
        vector<bool> selected(nums.size());
        backtrack(nums, selected, path, res);
        return res;
    }
    
    void backtrack(const vector<int>& nums, vector<bool>& selected, vector<int>& path, vector<vector<int>>& res) {
        // 获取到一个排列
        if (nums.size() == path.size()) {
            res.emplace_back(path);
            return;
        }
        // 选择数组元素填入 path 后
        for (int i = 0; i < nums.size(); i++) {
            // 跳过已使用过的元素
            if (selected[i]) {
                continue;
            }
            // 标记使用，压入 path
            selected[i] = true;
            path.push_back(nums[i]);
            // 搜索
            backtrack(nums, selected, path, res);
            // 回溯
            path.pop_back();
            selected[i] = false;
        }
    }
};
```

### 2. 基于交换的回溯

对于每个位置，在循环中用交换的方式将后面的各个元素都放到该位置

``` c++
TC=O(N*N!)
SC=O(N)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(nums, 0, res);
        return res;
    }
private:
    void backtrack(vector<int>& nums, int idx, vector<vector<int>>& res) {
        // 获取到一个排列
        if (idx == nums.size()) {
            res.push_back(nums);
            return;
        }
        // 对 idx 及之后的元素，依次交换到 idx 位置进行搜索并回溯
        for (int j = idx; j < nums.size(); j++) {
            swap(nums[idx], nums[j]);
            // 搜索
            backtrack(nums, idx + 1, res);
            // 回溯
            swap(nums[idx], nums[j]);
        }
    }
};
```
