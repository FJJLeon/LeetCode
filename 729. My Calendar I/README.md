# 729. My Calendar I

## 题目

题面：https://leetcode.com/problems/my-calendar-i/

预定 [start,end) 的日程，不能出现日程重复

## 实现

由于是不能重复，即同一时刻不能有两个日程，只需要 set 即可。

自定义结构体或者 pair，重写 operator < 用于 set 的比较。

``` c++

struct Interval{
    int start;
    int end;
    // 使得新来的 Interval 不重复于当前的 Interval，且按照 start 顺序排列
    // 注意这里不能把两种有重叠的情况都写进去，否则会在不发生重叠时无法区分大小顺序，造成混乱
    // 即不能写成 min(end, r.end) <= max(start, r.start)
    bool operator< (const Interval& r) const {
        if (end <= r.start) {
            return true;
        }
        return false;
    }
};
class MyCalendar {
public:
    set<Interval, less<Interval>> booked;
    MyCalendar() {
        
    }
    bool book(int start, int end) {
        return booked.insert(Interval{start, end}).second;
    }
};
```
