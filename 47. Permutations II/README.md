# 47. Permutations II

## 题目

题面：https://leetcode.com/problems/permutations-ii/

全排列，数组元素有重复

## 思路与实现

N个空位，从左往右选择数组元素填入。但数组元素有重复，每个位置不能填入同一个重复元素。

### 回溯

为保证对于每个位置，重复元素只填入一次，首先对数组排序，并利用一个布尔标记数组记录每个元素是否使用过。这样保证了重复元素只相邻出现，在填充时保证每一个位置只填入重复元素的第一个。

那么如何保证呢？遍历数组选择填充元素时，若发现当前元素与前一个元素重复，

* 若前一个元素未使用过，则说明这是同一个位置的元素选择，该重复元素已经在之前的循环中在当前位置被选择过
* 若前一个元素已使用过，则说明这是不同位置的元素选择，该重复元素在下一位置是可以被选择的

``` c++
TC=O(N*N!)
SC=O(N)

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        // 先排序
        sort(nums.begin(), nums.end());
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
            // 如何剪枝？首先元素需要未使用过
            // 若有重复元素，且前一个也未使用过，说明是同一个位置元素选择，重复元素在当前位置已经选择过，需要剪枝
            if (selected[i] || (i > 0 && nums[i] == nums[i-1] && !selected[i-1])) {
                continue;
            }
            // 标记使用，压入 path
            selected[i] = true;
            path.push_back(nums[i]);
            // 搜索
            bt(nums, selected, path, res);
            // 回溯，撤销标记，退栈
            path.pop_back();
            selected[i] = false;
        }
    }
};
```

值得注意的是，**i > 0 && nums[i] == nums[i-1] && !selected[i-1]** 剪枝条件的最后一项也可以是 **i > 0 && nums[i] == nums[i-1] && selected[i-1]**，全排列仍能得到，但是重复元素在全排列中的顺序相反，前者正序出现，后者倒序出现。另外，前者的剪枝效率更高。具体参考 [回溯搜索 + 剪枝（Java、Python）](https://leetcode.cn/problems/permutations-ii/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liwe-2/)