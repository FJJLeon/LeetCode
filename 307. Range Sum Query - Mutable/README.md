# 307. Range Sum Query - Mutable

## 题目

题面：https://leetcode.com/problems/range-sum-query-mutable/

[303](../303.%20Range%20Sum%20Query%20-%20Immutable/README.md)的扩展，可以修改数组。

## 思路与实现

### 1. 前缀和 TLE

仍使用前缀和，在更新某个索引值时，会影响该索引后的所有前缀和。

``` c++
TC: constructor = O(N) update = O(N), range sum = O(1)
SC = O(N)

class NumArray {
public:
    int n;
    vector<int> integra;
    NumArray(vector<int>& nums) {
        n = nums.size();
        integra.resize(n+1);
        for (int i = 1; i <= n; i++) {
            integra[i] = integra[i-1] + nums[i-1];
        }
    }
    
    void update(int index, int val) {
        // 获取index索引处 值的增量
        int diff = val - (integra[index+1] - integra[index]);
        // 更新index索引后的值
        for (int i = index+1; i <= n; i++) {
            integra[i] += diff;
        }
    }
    
    int sumRange(int left, int right) {
        return integra[right+1] - integra[left];
    }
};
```

### 2. 分块

直接使用前缀和在更新时需要更新所有后续块的前缀和，时间复杂度不可接受。一个优化是把数组分块，每个块只记录自己的和，在更新时只要更新所在块的和，在区间查询时可以直接使用块的和。

```
|----| |----| |----| |----| |----|  blocks
         bl                   br    块索引
       |----|               |----|  nums
         il                   ir    块内索引
```

``` c++
TC: constructor = O(N) update = O(1), range sum = O(sqrt(N))
SC = O(N)
class NumArray {
public:
    vector<int> blocks;
    int blockSize;
    vector<int> nums;
    NumArray(vector<int>& nums): nums(nums) {
        int n = nums.size();
        blockSize = sqrt(n);
        blocks.resize((n + blockSize - 1) / blockSize);
        // 分块求和
        for (int i = 0; i < n; i++) {
            blocks[i / blockSize] += nums[i];
        }
    }
    
    void update(int index, int val) {
        // 更新所在块的和
        blocks[index / blockSize] += val - nums[index];
        // 更新数组值
        nums[index] = val;
    }
    
    int sumRange(int left, int right) {
        int bl = left / blockSize, br = right / blockSize;
        int il = left % blockSize, ir = right % blockSize;
        // 区间在同一个块内，直接在元素数组中求和
        if (bl == br) {
            return accumulate(nums.begin() + left, nums.begin() + right + 1, 0);
        }
        // 在元素数组中计算左块靠右部分的和
        int leftSum = accumulate(nums.begin() + left, nums.begin() + (bl + 1) * blockSize, 0);
        // 计算中间块的和
        int internalSum = accumulate(blocks.begin() + bl + 1, blocks.begin() + br, 0);
        // 在元素数组中计算右块靠左部分的和
        int rightSum = accumulate(nums.begin() + br * blockSize, nums.begin() + right + 1, 0);
        return leftSum + internalSum + rightSum;
    }
};
```

其中，区间查询的时间复杂度为 $O(blockSize + \frac{n}{blockSize})$，其中 blockSize 为块大小，n 为数组长度。$blockSize + \frac{n}{blockSize} \ge 2 \sqrt{n}$，当且仅当 $blockSize = \sqrt{n}$ 时取等号，此时区间查询时间复杂度为 $O(\sqrt{n})$。

### 3. 树状数组

方法2中直接线性得对数组进行了分块，算法实现的查询时间复杂度为 $O(\sqrt{n})$。

另一种做法是使用树状数组，本质上也是一种分块，树状数组别称二叉搜索树(Binary Index Tree)，顾名思义，其分块方式利用了索引的二进制表示。

简单描述一下，首先定义了一个 **lowbit(x)** 函数，它返回 x 的最低位 1 所代表的值，可以用 x & (-x) 来计算。

树状数组也是计算一段区间和，但不是整个前缀和，而是计算 lowbit(x) 长度的区间和，即 **sum[i] = [i-lowbit(i)+1, i]**，形成了一个树状的区间和数组。利用这样的分层区间和计算机制，可以实现更新和查询的时间复杂度都为 O(logN)。

值得一提的是，在初始化构造时，若逐次调用 update，则总时间复杂度为 O(NlogN)，但若遍历整个数组，用已计算好的区间和来构造，则时间复杂度为 O(N)，参见代码。

Reference：
* [原来树状数组可以这么简单？](https://mp.weixin.qq.com/s/phCKhdXYbt-vUDPYcF_AnQ)
* [树状数组，看这一篇就够了](https://mp.weixin.qq.com/s/ZogMdq7r6qKT8aEHJmON_g)
``` c++
TC: constructor = O(N) update = O(log(N)), range sum = O(log(N))
SC: O(N)
class BIT {
public:
    int n;
    // 1-index 
    vector<int> sums; 
    BIT(int n) {
        sums.resize(n+1);
    }
    // 根据给定数组的 O(N) 构造，优于 N 次调用 update
    BIT(vector<int>& nums) {
        n = nums.size();
        sums.resize(n+1);
        for (int i = 1; i <= n; i++) {
            sums[i] = nums[i-1];
        }
        for (int i = 1; i <= n; i++) {
            int j = i + lowbit(i);
            if (j <= n)
                sums[j] += sums[i];
        }
    }
    
    inline int lowbit(int x) {
        return x & -x;
    }
    // 索引 index 处值增加 x
    void add(int index, int x) {
        while (index <= n) {
            sums[index] += x;
            index += lowbit(index);
        }
    }
    // 查询 [1, index] 前缀和
    int query(int index) {
        int res = 0;
        while (index > 0) {
            res += sums[index];
            index -= lowbit(index);
        }
        return res;
    }
};

class NumArray {
public:
    vector<int> nums;
    BIT* bit;
    NumArray(vector<int>& nums) : nums(nums) {
        // 初始化 BIT
        bit = new BIT(nums);
    }
    
    void update(int index, int val) {
        // 计算增量
        int diff = val - nums[index];
        // 更新原数组
        nums[index] = val;
        bit->add(index + 1, diff);
    }
    
    int sumRange(int left, int right) {
        // 计算区间和 [left, right] = [1,right+1] - [1,left]
        return bit->query(right+1) - bit->query(left);
    }
};
```
