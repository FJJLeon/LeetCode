# 1642. Furthest Building You Can Reach

## 题面

题目：https://leetcode-cn.com/problems/furthest-building-you-can-reach/

给定的整数表示建筑的高度，从 0 开始，若下一个建筑的高度相比当前建筑一致或较低，可以直接过去，否则需要搭梯子或者使用砖块。

梯子可以直接爬上建筑，而砖块需要 h[i+1] - h[i] 块。

在给定数量的砖块和梯子的情况下，计算你可以爬到的最远建筑索引。

## 思路与实现

初见可能认为这是一个搜索或者动态规划的问题，实际上可以用贪心的思路，一个梯子相当于无限高的砖块，但是只能用在一次。

### 1. 贪心

从左向右遍历，保留建筑升高的长度，用一个优先队列（小顶堆）保存，若队列数量超过梯子数量则需要使用砖块，从优先队列中取出最小的那个使用砖块，直到砖块不够用为止。

``` c++
TC=O(NlogK), K = 梯子数量
SC=O(K)

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        // 优先队列，较小的排在前面
        priority_queue<int, vector<int>, greater<int>> topL;
        int n = heights.size();
        // 从左到右遍历
        for (int i = 1; i < n; i++) {
            // 如果当前建筑高度比上一建筑高度高，则将差值加入优先队列
            int diff = heights[i] - heights[i - 1];
            if (diff > 0) {
                topL.push(diff);
                // 若优先队列大小超过梯子数量，则需要使用砖块
                if (topL.size() > ladders) {
                    // 取出最小的那个使用砖块
                    bricks -= topL.top();
                    topL.pop();
                }
                // 若砖块不够用，则不能继续
                if (bricks < 0)
                    return i - 1;
            }
        }
        // 走完全程，返回最后一个建筑的索引
        return n - 1;
    }
};
```
