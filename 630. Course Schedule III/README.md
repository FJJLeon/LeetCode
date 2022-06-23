# 630. Course Schedule III

## 题目

题面：https://leetcode-cn.com/problems/course-schedule-iii/

每门课有一个花费时间和一个DDL，问最多能上几门课。


## 思路与实现

到底是Hard题，如何构造贪心操作较难想到。

基于一个原则，优先上DDL早的课。将课程按DDL由近及远排序，优先上DDL近的课，用一个优先队列保存已经上过的课，若发现某门课上不了了，那就要从队列中去除花费时间最多的课，用当前课替换。

``` c++
TC=O(NlogN)
SC=O(N)

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 按课程DDL升序排列
        sort(courses.begin(), courses.end(), 
             [&](vector<int>& v1, vector<int>& v2) {return v1[1] < v2[1];}
            );
        // 优先队列存储已上过的课，保存花费时间
        priority_queue<int> pq;
        // 优先队列中课程的总花费时间
        int sum = 0;
        for (auto& c : courses) {
            sum += c[0];
            pq.push(c[0]);
            // 上了这门课会超过DDL，则要取出花费时间最多的课
            if (sum > c[1]) {
                sum -= pq.top();
                pq.pop();
            }
        }
        
        return pq.size();
    }
};
```
