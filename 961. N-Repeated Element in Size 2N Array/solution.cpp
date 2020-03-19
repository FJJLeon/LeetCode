#include<vector>
#include<unordered_set>

using namespace std;

/**
 * 遍历，用 set 记录，发现重复
 * 
 * Runtime: 40 ms, faster than 86.04%, O(N)
 * Memory Usage: 10 MB, less than 100.00%, O(N)
*/
class Solution1 {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_set<int> exist;
        for (int i : A) {
            if (exist.count(i))
                return i;
            exist.insert(i);
        }
        // won't reach
        return 0;
    }
};


/**
 * 优化空间复杂度 O(1), asked by MEITUAN(zzt)
 * 
 * 脑瓜子想一下，2N 个 数里找到重复 N 次的数(x)，那么必然能在所有连续的三元组中找到 x 重复
 * 除了数组大小为 4，且形如 [x, a, b, x]、[x, x, a, b], 此时返回 A[0] 即可
 * 注意比较元素是三元组最后一个（也可以是第一个，相应反例变为[x, a, b, x] 和 [a, b, x, x]）
 * 
 * Runtime: 40 ms, faster than 86.04%, O(N)
 * Memory Usage: 9.7 MB, less than 100.00%, O(1)
*/
class Solution2 {
public:
    int repeatedNTimes(vector<int>& A) {
        for (int i = 2; i < A.size(); ++i)
            // compare elem is the third one of every ternary array
            if (A[i] == A[i - 1] || A[i] == A[i - 2])
                return A[i];
        return A[0];
    }
};
