# [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

## 题面

将一个严格递增的数组转换为高度平衡树(AVL树)，每个节点的子树高度差小于等于 1。


## 实现

由于数组严格递增，我们可以将数组分成三份，中间一个节点，左侧所有节点组成节点左子树，右侧所有节点组成节点右子树，然后对左右部分进行递归调用，得到的结果才真正作为左右子树。

### 1. 递归

递归实现，可以对数组进行切片递归调用，但是切片复制会导致时间复杂度升高；因此可以使用索引或迭代器进行实现。

``` c++
TC=O(N)
SC=O(logN)

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return divide(nums, 0, size(nums) - 1);
    }
    // 索引实现
    TreeNode* divide(vector<int>& nums, int l, int r) {
        if (l > r)
            return nullptr;
        int m = l + (r - l) / 2;
        TreeNode* root = new TreeNode(nums[m]);
        root->left = divide(nums, l, m - 1);
        root->right = divide(nums, m + 1, r);
        return root;
    }
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return divide(nums.begin(), nums.end());
    }
    // 迭代器实现
    using it = vector<int>::const_iterator;
    TreeNode* divide(it b, it e) {
        if (b == e)
            return nullptr;
        it m = b + (e - b) / 2;
        TreeNode* root = new TreeNode(*m);
        root->left = divide(b, m);
        root->right = divide(m + 1, e);
        return root;
    }
};
```

### 2. 迭代

使用 stack 将递归实现转换为迭代实现，stack 中需要存储树节点和该节点树覆盖的数组范围，使用 tuple 或 struct 维护。

``` c++
TC=O(N)
SC=O(logN)

class Solution {
public:
    using Cover = tuple<int, int, TreeNode*>;
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n = nums.size();
        stack<Cover> st;
        // 根节点入 stack
        TreeNode* root = new TreeNode(nums[(n-1)/2]);
        st.push({0, n - 1, root});
        
        auto getMid = [](int l, int r) -> int {return l + (r - l) / 2;};
        while (!st.empty()) {
            auto [l, r, parent] = st.top(); st.pop();
            int mid = getMid(l, r);
            // 左子树
            if (mid - 1 >= l) {
                TreeNode* left = new TreeNode(nums[getMid(l, mid - 1)]);
                parent->left = left;
                st.push({l, mid - 1, left});
            }
            // 右子树
            if (r >= mid + 1) {
                TreeNode* right = new TreeNode(nums[getMid(mid + 1, r)]);
                parent->right = right;
                st.push({mid + 1, r, right});
            }
        }
        return root;
    }
};
```
