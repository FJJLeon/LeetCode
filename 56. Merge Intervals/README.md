# 56. Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

Example:
```
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
```

Idea: 
* Sort intervals by begin index, then linear scan each interval and compare end index with previous to merge overlap or not