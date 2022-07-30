# 952. Largest Component Size by Common Factor

## 题目

题面：https://leetcode-cn.com/problems/largest-component-size-by-common-factor/

给定一组数字，若两个数有大于1的公因数，则这两个数之间有边，求该图最大连通分量的大小。

## 思路与实现

### 1. 直接建图求连通分量

对于每两个数字，求最大公约数，若大于1，则两数连通。

对于求连通分量的实现，可以建图后 BFS/DFS 求连通分量，另一种是使用并查集 UnionFind。

``` c++
TC=O(N^2*logN*αN)
SC=O(N)

class Solution {
private:
    // 并查集实现
    const static int N = 1e5 + 10;
    int parent[N];
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py)
            parent[px] = py;
    }
    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }
public:
    int cnt[N]
    int largestComponentSize(vector<int>& nums) {
        // 为每个数字分配一个单独分组
        int m = *max_element(nums.begin(), nums.end()) + 1;
        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }
        // 对每对数字gcd求最大公约数，若大于1，则两数连通，进行合并
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (gcd(nums[i], nums[j]) > 1) 
                    merge(nums[i], nums[j]);
            }
        }
        // 对每个分组的根代表计算连通分量大小，求最大值
        int res = 0;
        for (int i = 0; i < n; i++) {
            res = max(res, ++cnt[find(nums[i])]);
        }
        return res;
    }
    int gcd(int x, int y) {
        if (y == 0)
            return x;
        return gcd(y, x % y);
    }
};
```

然而超时。

### 2. 因数分解建图求连通分量

每两个数进行公约数连通需要O(N^2)时间，由于是数字，可以使用因数进行间接连通合并。

比如，6 分解与因数 2、3 连通，18 分解与因数 2、3、6、9 连通，由于有共同因数 3，因此 6、18 连接连通，每个数因数分解可以在 O(N * sqrtN) 时间。

``` c++
TC=O(N*sqrtM*αM)
SC=O(N)

class Solution {
private:
    const static int N = 1e5 + 10;
    int parent[N];
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py)
            parent[px] = py;
    }
    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }
public:
    int cnt[N];
    int largestComponentSize(vector<int>& nums) {
        // 为每个数字分配一个单独分组
        int m = *max_element(nums.begin(), nums.end()) + 1;
        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }
        // 对于每个数，进行因数分解，与每个因数分别连通合并
        for (int num : nums) {
            for (int i = 2; i <= sqrt(num); i++) {
                if (num % i == 0) {
                    merge(num, i);
                    merge(num, num / i);
                }
            }
        }
        
        int res = 1;
        for (int num : nums) {
            res = max(res, ++cnt[find(num)]);
        }
        return res;
    }
};
```

可以看到，因数分解中有很多冗余连通，比如因数 3、6、9 其实都是连通到 3 的，可以进一步采用质因数分解来优化。

``` c++
TC=O(N*sqrtM*αN)
SC=O(N)
class Solution {
private:
    const static int N = 1e5 + 10;
    int parent[N];
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py)
            parent[px] = py;
    }
    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }
public:
    int cnt[N];
    int largestComponentSize(vector<int>& nums) {
        // 为每个数字分配一个单独分组
        int m = *max_element(nums.begin(), nums.end()) + 1;
        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }
        // 对于每个数，进行质因数分解，与每个质因数分别连通合并
        for (int num : nums) {
            int cur = num;
            for (int i = 2; i <= sqrt(cur); i++) {
                if (cur % i == 0) {
                    merge(num, i);
                    // 把该因数除完
                    while (cur % i == 0)
                        cur /= i;
                }
            }
            // 若余商大于 1，进行连通合并
            if (cur > 1)
                merge(num, cur);
        }
        int res = 1;
        for (int num : nums) {
            res = max(res, ++cnt[find(num)]);
        }
        return res;
    }
};
```

也可以先把所有最大数以内的质因数找出来，然后再进行质因数分解。

``` c++
TC=O(N + N*logM*αM)
SC=O(N)

const static int N = 1e5 + 10;
int isPrime[N], primes[N];
int p = 0;
// 欧拉筛，预处理找出 N 以内的质因数
int _ = [] {
    for (int i = 2; i < N; i++) {
        if (isPrime[i] == 0) {
            primes[p++] = i;
        }
        for (int j = 0; primes[j] * i < N; j++) {
            isPrime[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    return 0;
}();

class Solution {
private:
    vector<int> parent;
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py)
            parent[px] = py;
    }
    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }
public:
    vector<int> cnt;
    int largestComponentSize(vector<int>& nums) {
        int m = *max_element(nums.begin(), nums.end()) + 1;
        vector<int>(m, 0).swap(parent);
        vector<int>(m, 0).swap(cnt);
        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }
        // 对于每个数，进行质因数分解，与每个质因数分别连通合并
        for (int num : nums) {
            int quotient = num;
            // 仅使用筛选出来的质数进行质因数分解
            for (int j = 0; j < p && primes[j] * primes[j] <= quotient; j++) {
                if (quotient % primes[j] == 0) {
                    merge(num, primes[j]);
                    while (quotient % primes[j] == 0)
                        quotient /= primes[j];
                }
            }
            if (quotient > 1) merge(quotient, num);
        }
        
        int res = 1;
        for (int num : nums) {
            res = max(res, ++cnt[find(num)]);
        }
        return res;
    }
};
```

### Reference

1. [按公因数计算最大组件大小【埃氏筛&欧拉筛+并查集（图解）】](https://leetcode.cn/problems/largest-component-size-by-common-factor/solution/an-gong-yin-shu-ji-suan-zui-da-zu-jian-d-0tm8/)
