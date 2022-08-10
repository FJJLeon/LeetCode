# 双周赛 84

20220806

## [T1. 2363. 合并相似的物品](https://leetcode.cn/problems/merge-similar-items/)

两个物品数组，每个数组的一项 **[value, weight]** 代表一个物品，其中每个物品数组内的物品价值是唯一的，合并两个物品数组，新物品重量为所有相等价值物品重量之和。

### 暴力

使用 map 进行暴力合并

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        map<int, int> mp;
        for (auto& it : items1) {
            mp[it[0]] = it[1];
        }
        for (auto& it : items2) {
            mp[it[0]] += it[1];
        }
        vector<vector<int>> res;
        // 利用 c++ map 的有序性
        // 若使用 unordered_map 则需要对 结果vector 进行排序
        for (auto& it : mp) {
            res.push_back({it.first, it.second});
        }
        return res;
    }
};
```

## [T2. 2364. 统计坏数对的数目](https://leetcode.cn/problems/count-number-of-bad-pairs/)

对于给定数组其中的数对，若索引差与数值差不相等，则是坏数对，统计坏数对的数目。

### 1. 暴力，TLE

对于一个数对 **nums[i], nums[j], i < j**，若 **j - i != nums[j] - nums[i]**，则是一个坏数对；那么**j - i == nums[j] - nums[i]** 是一个好数对。

一个暴力做法是对于每个数对进行判断，计算坏数对的数目，时间复杂度为 O(N^2)；无论判断的是好坏数对，都需要所有数对，不影响时间复杂度，都会超时。

``` c++
TC=O(N^2)
SC=O(1)

class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        long long res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int ni = nums[i];
            for (int j = i + 1; j < n; j++) {
                if (j - i != nums[j] - ni)
                    res++;
            }
        }
        return res;
    }
};
```

### 2. 分组

对于每个数对的判断非常有误导性，我们对判断式进行移项 **nums[j] - j != nums[i] - i**，可以发现实际上这里判断的是数组中**索引值和数值的差值**不同，我们可以将每个数按照该差值进行分组。

对于每个分组，组内的数对差值都相等，组内的每个数对均是好数对，组内的每个数与组外的其他数均组成坏数对。我们可以使用总数对减去所有好数对，也可以直接计算组外坏数对。

``` c++
TC=O(N)
SC=O(N)

// 组内的每个数与组外的其他数均组成坏数对
class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        long long res = 0;
        int n = nums.size();
        vector<int> visit(n);
        map<int, int> group;
        for (int i = 0; i < n; i++) {
            // 该组内数量 +1
            group[nums[i] - i]++;
        }
        for (auto [_, cnt] : group) {
            // 计算坏数对，组内 * 组外
            res += cnt * (n - cnt);
        }
        // 注意坏数对形成是相互的，需要取半
        return res / 2;
    }
};

// 总数对减去所有好数对
class Solution {
public:
    // 计算一个分组内总数对数目
    long long countGroup(long long groupN) {
        return groupN * (groupN - 1) / 2;
    }
    long long countBadPairs(vector<int>& nums) {
        long long res = 0;
        int n = nums.size();
        vector<int> visit(n);
        map<int, int> group;
        for (int i = 0; i < n; i++) {
            group[nums[i] - i]++;
        }
        for (auto [_, cnt] : group) {
            // 计算好数对，组内总数对
            res += countGroup(cnt);
        }
        // 总数对 - 好数对
        return countGroup(n) - res;
    }
};
```

本题也可以在进行分组计数的同时计算坏数对数目。

``` c++
TC=O(N)
SC=O(N)

class Solution {
public:
    long long countGroup(long long groupN) {
        return groupN * (groupN - 1) / 2;
    }
    long long countBadPairs(vector<int>& nums) {
        long long res = 0;
        int n = nums.size();
        vector<int> visit(n);
        map<int, int> group;
        for (int i = 0; i < n; i++) {
            // 当前数 与 前面的同组数 形成好数对
            res += group[nums[i] - i];
            // 该组内数量 +1
            group[nums[i] - i]++;
        }
        return countGroup(n) - res;
    }
};
```

## [T3. 2365. 任务调度器 II](https://leetcode.cn/problems/task-scheduler-ii/)

对于给定的任务数组，只能按顺序完成任务。每个任务有一定的类型，两个相同类型的任务中间最少需要相隔 space 天，指前一个任务完成后到下一个任务开始前需要间隔 space 天。

### 1. 使用 map 模拟，TLE

在模拟过程中，使用 map 记录每个任务类型的的剩余冷却时间，即 space 减去上一个该类型任务完成后过去的时间。
在模拟过程中，对于下一个任务，若该类型任务剩余时间大于 0，则需要进行冷却，否则可以立即完成。

``` c++
TC=O(NM), N 为任务长度，M 为任务类型数量
SC=O(M)

class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long long res = 0;
        // 使用 map 记录每个任务类型的的剩余冷却时间
        unordered_map<int, int> taskRemain;
        for (int& t : tasks) {
            // 该类型任务剩余时间大于 0，则需要进行冷却
            if (taskRemain[t] > 0) {
                res += taskRemain[t] + 1;
                // 对所有任务冷却时间减去 taskRemain[t] + 1
                decMap(taskRemain, taskRemain[t] + 1);
            }
            // 可以立即完成
            else {
                res += 1;
                // 对所有任务冷却时间减去 1
                decMap(taskRemain, 1);
            }
            // 重新设置该类型任务冷却时间
            taskRemain[t] = space;
        }
        return res;
    }
    // 对 map 中所有任务的冷却时间减去 dec
    // 若冷却时间小于 0，任务是已完成
    // 即使删除小于 0 的项，仍旧会超时
    void decMap(unordered_map<int, int>& m, int dec) {
        for (auto& p : m) {
            p.second -= dec;
        }
    }
};
```

### 2. 使用 time 模拟

上述模拟过程中维护了每个类型任务的剩余冷却时间，需要每次对所有冷却时间进行修改，这步操作需要 O(M) 时间。

然而，应该在 map 中维护对于每个类型任务的上一个完成时间，这样在 time 变化时便隐式得可计算所有类型任务的冷却时间，即 time - taskTime[task]，若该值小于等于 space 则需要进行冷却。

``` c++
TC=O(N) - unordered_map, O(NlogM) - map
SC=O(M)

class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long long time = 0;
        int n = tasks.size();
        // 记录每个任务类型的的上一个完成时间
        unordered_map<int, long long> taskTime;
        for (int i = 0; i < n; i++) {
            int t = tasks[i];
            time += 1;
            // 已经进行过该类型任务，且距现在时间小于等于冷却时间
            if (taskTime.count(t) == 1 && time - taskTime[t] <= space) {
                time += space - (time - taskTime[t]) + 1;
            }
            // 重新设置该类型冷却时间
            taskTime[t] = time;
        }
        return time;
    }
};

class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long long time = 0;
        int n = tasks.size();
        unordered_map<int, long long> taskTime;
        for (int i = 0; i < n; i++) {
            int t = tasks[i];
            // 已经进行过该类型任务，且距现在时间小于等于冷却时间
            if (taskTime.count(t) && taskTime[t] + space > time)
                // 直接进行赋值，用完冷却时间
                time = taskTime[t] + space + 1;
            else
                time += 1;
            taskTime[t] = time;
        }
        return time;
    }
};
```

## [T4. 2366. 将数组排序的最少替换次数](https://leetcode.cn/problems/minimum-replacements-to-sort-the-array/)

对于给定数组，可以不断得拆分数组中的数变成两个数，使得整个数组非递减，即非严格递增，返回最少拆分次数

### 1. 贪心

考虑这样一种贪心策略，首先数组元素顺序不可调换，数组最后一个元素必然无需拆分。那么对于倒数第二个数，如何拆分能使得拆分次数尽可能少呢？必然是在小于等于最后一个数的情况下尽可能平均拆分，使得拆分后的最小元素尽量大，这样对更前面的数影响尽量小。

考虑到可能无法完全平均拆分，此时只能将较小的那个放在前面，即需要将拆分 ceil(当前数 / 后一个数) = k 次，其中较小的那个数为 floor(当前数 / k)。

``` c++
TC=O(N)
SC=O(N) / O(1)

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long long cnt = 0;
        int n = nums.size();
        vector<int> lastMin(n);
        lastMin.back() = nums.back();
        for (int i = n - 2; i >= 0; i--) {
            // nums[i] 需要拆分成几个数
            // int k = ceil((double)nums[i] / lastMin[i+1]);
            int k = (nums[i] + lastMin[i+1] - 1) / lastMin[i+1];
            // 拆分次数
            cnt += k - 1;
            // 记录拆分后最小的那个数
            // lastMin[i] = floor((double)nums[i] / k);
            lastMin[i] = nums[i] / k;
        }
        return cnt;
    }
};

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long long cnt = 0;
        int n = nums.size();
        // 只需记录最近一个
        int last = nums.back();
        for (int i = n - 2; i >= 0; i--) {
            // nums[i] 需要拆分成几个数
            int k = (nums[i] + last - 1) / last;
            // 拆分次数
            cnt += k - 1;
            // 记录拆分后最小的那个数
            last = nums[i] / k;
        }
        return cnt;
    }
};
```
