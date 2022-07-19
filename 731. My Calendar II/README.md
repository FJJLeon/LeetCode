# 731. My Calendar II

## 题目

题面：https://leetcode-cn.com/problems/my-calendar-ii/

用 [start, end) （均为整数）表示的时间段预定日程，至多同一时间点可以有两个日程，即在预定时如果发现已经有两个日程与之冲突，则放弃预定。

## 思路与实现

是一个区间查询的问题，每次预定时都需要确定给定区间中（是否有某个时间点）已有日程数量大于等于 2（当然实际上不可能大于 2）。需要保证每个时间点的日程数量都小于 2，才可以进行预定，这查询的即为区间最大值。区间最大值与区间和类似，可以用**子区间归并**（max(l,r) = max(max(l,mid),max(mid+1, r)）得到，故可以使用线段树保存区间。

### 1. 暴力

用两个数组分别保存没有冲突的区间和已有冲突的区间。

对于新来的预定区间，遍历所有已有冲突的区间，若再次有冲突，则放弃预定；再遍历所有没有冲突的区间，若有冲突，则将冲突区间放入已有冲突的区间。最后将新来的预定区间放入没有冲突的区间，当然也可以根据冲突区间进行缩小，实际上没有必要。

### 2. 差分数组

用差分数组（这里要用有序map）表示区间，插入新区间时只要更新两个端点，然后检查所有区间端点处实际值，若大于 2 则此区间不可预定。

``` c++
TC=O(N^2)
SC=O(N)

class MyCalendarTwo {
public:
    MyCalendarTwo() {

    }
    
    bool book(int start, int end) {
        int maxBook = 0;
        // 左端点 +1，右端点 -1，注意是左闭右开，若右也闭，则为 cnt[end+1]--
        cnt[start]++;
        cnt[end]--;
        // 计算所有区间端点处实际值，累加求和
        for (auto [_, freq] : cnt) {
            maxBook += freq;
            // 若实际值大于 2，则此区间不可预定
            if (maxBook > 2) {
                cnt[start]--;
                cnt[end]++;
                return false;
            }
        }
        return true;
    }
private:
    // 有序 map，才能从小到大顺序遍历区间端点
    map<int, int> cnt;
};
```

### 3. 线段树 + 动态开点

用线段树保存区间最大值。

``` c++
TC=O(NlogC), C = 1e9
SC=O(NlogC)

struct Node {
    Node *ls, *rs;
    int maxi, add;
    Node(Node* _ls = nullptr, Node* _rs = nullptr, int _maxi = 0, int _add = 0) : ls(_ls), rs(_rs), maxi(_maxi), add(_add) {}
};

class MyCalendarTwo {
private:
    int N = (int)1e9;
    Node *root;
    void update(Node *node, int left, int right, int start, int end, int val) {
        if (start <= left && right <= end) {
            node->add += val;
            node->maxi += val;
            return;
        }
        pushdown(node);
        int mid = left + right >> 1;
        if (start <= mid) update(node->ls, left, mid, start, end, val);
        if (end > mid) update(node->rs, mid + 1, right, start, end, val);
        pushup(node);
    }
    int query(Node* node, int left, int right, int start, int end) {
        if (start <= left && right <= end) return node->maxi;
        pushdown(node);
        int mid = left + right >> 1, ans = 0;
        if (start <= mid) ans = query(node->ls, left, mid, start, end);
        if (end > mid) ans = max(ans, query(node->rs, mid + 1, right, start, end));
        return ans;
    }
    void pushdown(Node* node) {
        if (node->ls == nullptr) node->ls = new Node();
        if (node->rs == nullptr) node->rs = new Node();
        int add = node->add;
        node->ls->maxi += add;
        node->rs->maxi += add;
        node->ls->add += add;
        node->rs->add += add;
        node->add = 0;
    }
    void pushup(Node* node) {
        node->maxi = max(node->ls->maxi, node->rs->maxi);
    }
public:
    MyCalendarTwo() : root(new Node) {
        
    }
    
    bool book(int start, int end) {
        if (query(root, 0, N, start, end - 1) >= 2) 
            return false;
        update(root, 0, N, start, end - 1, 1);
        return true;
    }
};
```

### Reference

1. [
我的日程安排表 II](https://leetcode.cn/problems/my-calendar-ii/solution/wo-de-ri-cheng-an-pai-biao-ii-by-leetcod-wo6n/)
2. [【宫水三叶】线段树（动态开点）的两种方式](https://leetcode.cn/problems/my-calendar-ii/solution/by-ac_oier-a1b3/)

