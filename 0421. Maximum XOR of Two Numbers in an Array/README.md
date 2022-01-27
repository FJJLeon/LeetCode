# 421. Maximum XOR of Two Numbers in an Array

## 描述

题面：https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

从给定数组中找到两个数，得到最大的异或值

## 思路与实现

首先这题暴力解法如下，计算所有异或值并比较

``` c++
T = O(N^2) TLE
S = O(1)

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            int num1 = nums[i];
            for (int j = i + 1; j < n; j++) {
                res = max(res, num1 ^ nums[j]);
            }
        }
        
        return res;
    }
};
```

就是说用 nums[i] 与之后的每个数得到异或结果，保留最大值；也可以说是用 nums[j] 与之前的每个数得到异或结果。但是这样做是超时的，现在的关键是异或运算。

要得到最大的异或结果，从贪心的思想考虑，要求两个数二进制表示中不同的位尽可能在高位，且尽可能得多。因此需要按位进行比较，对于一个数，要找到与之二进制表示中差异位尽可能高且多的另一个数，从而得到最大异或结果，使用前缀树Trie可以完成这一目标。

第一步，对于每个数，从二进制高位到低位遍历每一位从而构建Trie；第二步，对于每个数num，尽可能按每位异或结果为1的方向搜索Trie，从而得到使用当前数 num 能得到的最大异或结果。


### 贪心 + 前缀树Trie

``` c++
T = O(31*N) = O(N)
S = O(31*N) = O(N)

class Trie {
private:
    Trie* children[2] = {};
public:
    Trie() {};

    // 将 num 加入 Trie
    void add(int num) {
        Trie* cur = this;
        // 从高位向低位遍历
        for (int i = 31; i >= 0; i--) {
            // 获取当前位，0 或 1
            int idx = (num >> i) & 1;
            // 如果Trie中没有该子节点，新建
            if (!cur->children[idx])
                cur->children[idx] = new Trie();
            // 前进到对应节点
            cur = cur->children[idx];
        }
    }
    
    // 找到在本 Trie 中对输入 num 能得到的最大异或结果
    int findMaxXOR(int num) {
        int res = 0;
        Trie* cur = this;
        for (int i = 31; i >= 0; i--) {
            // 获取当前位，0 或 1
            int idx = (num >> i) & 1;
            // 优先走与输入 num 二进制第 i 位（即 idx）不同的方向，从而能异或置位结果 res
            if (cur->children[idx ^ 1]) { // idx ^ 1 得到相反位，若存在该节点，则异或值能包含该位
                res |= 1 << i;
                cur = cur->children[idx ^ 1];
            }
            // 不存在相反位节点，只能不走
            else if (cur->children[idx]) {
                cur = cur->children[idx];
            }
        }
        
        return res;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        Trie* root = new Trie();

        // 被注释的实现先建整棵树再搜索每个数，
        // 实际上没有必要，可以搜索一个加入一个
        // for (int& num : nums) {
        //     root->add(num);
        // }
        // for (int& num : nums) {
        //     res = max(res, root->findMaxXOR(num));
        // }

        for (int& num : nums) {
            res = max(res, root->findMaxXOR(num));
            root->add(num);
        }
        
        return res;
    }
};
```

### 掩码 + 集合

首先该解法利用了异或的一个性质
```
a ^ b = c -> a ^ c = b, b ^ c = a
```

不用Trie，使用类似的思路，从高位到低位一位一位得到最大异或值。利用掩码获取数组的 “前缀” 集合，判断是否存在两个数能异或得到潜在的更好结果。

根据代码解释

``` c++
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        // res 记录从高位向低位迭代过程中获取到的最大异或值
        // mask 用于获取前缀
        int res = 0, mask = 0;
        // 贪心得从高位到低位判断能否在异或结果中包含该位
        for (int i = 31; i >= 0; i--) {
            // mask 左半部分为1，右半部分为0，1的个数为迭代次数
            mask |= 1 << i;
            set<int> prefixs;
            for (int& num : nums) {
                // 获取数组的前缀集合
                prefixs.insert(num & mask);
            }
            // 这是一个潜在的更好异或结果，即用之前的res并将当前迭代对应的位置为1
            int cand = res | (1 << i);
            // 对于前缀集合中的每个前缀
            for (int prefix : prefixs) {
                // 若 prefix ^ cand 同时也在前缀集合中存在，意味着该潜在结果 cand 是可以得到的
                if (prefixs.find(prefix ^ cand) != prefixs.end()) {
                    res = cand;
                    break;
                }
            }
        }
        
        return res;
    }
};
```

算法在迭代中从高位到低位确定了每一位是否可以在最大异或结果中置位。迭代过程实际上按照贪心的策略不断缩小产生最大异或结果的范围，**cand = res | (1 << i)** 囊括了之前的高位结果，只有能产生高位结果的数才能被作为候选。

以示例数据 [3, 10, 5, 25, 2, 8] 为例
```
     binary  prefix,i=4
3  = 00011     0-
10 = 01010     0-
5  = 00101     0-
25 = 11001     1-
2  = 00010     0-
8  = 01000     0-

cand = 1-
25 的前缀可以与其他数异或得到 cand，现在所有数仍能候选
res = 1-

     binary  prefix,i=3
3  = 00011     00-
10 = 01010     01-
5  = 00101     00-
25 = 11001     11-
2  = 00010     00-
8  = 01000     01-

潜在结果 cand = 11-
25 的前缀可以与 {3, 5, 2} 的前缀异或得到 cand
res = 11-

     binary  prefix,i=2
3  = 00011     000-
10 = 01010     010-
5  = 00101     001-
25 = 11001     110-
2  = 00010     000-
8  = 01000     010-

cand = 111-
此时 {10, 8} 实际上已经不在候选集合中了，他们的高位与 cand 异或的结果都不在集合中，更何况现在位数更多了
现在只有 25 的前缀与 5 的前缀异或能得到 cand
res = 111-

循环实际上已经可以结束

     binary  prefix,i=1
3  = 00011     0001-
10 = 01010     0101-
5  = 00101     0010-
25 = 11001     1100-
2  = 00010     0001-
8  = 01000     0100-

cand = 1111-
任一前缀与 cand 的异或结果都不存在，不能置位
res = 1110-

同理

res = 11100
```

与前缀树的实现类似，每次对位数的大迭代中的两次遍历实际上可以合并，只要单向搜索一遍即可

``` c++
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        // res 记录从高位向低位迭代过程中获取到的最大异或值
        // mask 用于获取前缀
        int res = 0, mask = 0;
        // 贪心得从高位到低位判断能否在异或结果中包含该位
        for (int i = 31; i >= 0; i--) {
            // mask 左半部分为1，右半部分为0，1的个数为迭代次数
            mask |= 1 << i;
            set<int> prefixs;

            // 这是一个潜在的更好异或结果，即用之前的res并将当前迭代对应的位置为1
            int cand = res | (1 << i);
            for (int& num : nums) {
                int prefix = num & mask
                // 若 prefix ^ cand 同时也在前缀集合中存在，意味着该潜在结果 cand 是可以得到的
                if (prefixs.find(prefix ^ cand) != prefixs.end()) {
                    res = cand;
                    break;
                }
                // 加入前缀集合
                prefixs.insert(prefix);
            }
        }
        
        return res;
    }
};
```

## 参考

[Java O(n) solution using bit manipulation and HashMap](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap)

[利用异或运算的性质、假设修正](https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/li-yong-yi-huo-yun-suan-de-xing-zhi-tan-xin-suan-f/)

[【宫水三叶の相信科学系列】详解为何能用「贪心」&「Trie」找「最大异或结果」](https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-bmjdg/)

[C++：Trie模板题（送板子）](https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/ctriemo-ban-ti-song-ban-zi-by-xiaoneng-tegw/)