#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

/**
 * DP
 * maintain a m*n size dp vector
 * dp[i][j] = LCS for s1[0..i] & s2[0..j]
 * dp[i][j] = dp[i-1][j-1] + 1, s1[i] == s2[j]
 *            max(dp[i-1][j], dp[i][j-1]), s1[i] != s2[j]
 * 
 * Runtime: 20 ms, O(MN)
 * Memory Usage: 12.8 MB, O(MN)
*/
class Solution11 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        // text1[0] & text2[0]
        dp[0][0] = text1[0] == text2[0];
        // text1[0..m-1] & text2[0]
        for (int i = 1; i < m; ++i)
            dp[i][0] = max(dp[i-1][0], (int)(text1[i] == text2[0]));
        // text1[0] & text2[0..n-1]
        for (int j = 1; j < n; ++j)
            dp[0][j] = max(dp[0][j-1], (int)(text1[0] == text2[j]));
        // text1[1..m-1] & text2[1..n-1]
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (text1[i] == text2[j])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m-1][n-1];
    }
};
/**
 * Simplify code, utilizes (m+1)*(n+1) dp vector, border for empty string
*/
class Solution12 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // i-1 and j-1 is index of string
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};
/**
 * Memory oprimization, only two row is useful
 * maintain two row of dp vector, use ^ to switch
 * 
 * Runtime: 24 ms, faster than 39.91%, O(M*N)
 * Memory Usage: 6.4 MB, less than 100.00%, O(min(M,N))
*/
class Solution13 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        if (m < n)  return longestCommonSubsequence(text2, text1);
        vector<vector<int>> dp(2, vector<int>(n + 1, 0));
        for (int i = 0, r = 1; i < m; ++i, r ^= 1)
            for (int j = 0; j < n; ++j)
                if (text1[i] == text2[j])
                    dp[r][j + 1] = 1 + dp[r ^ 1][j];
                else 
                    dp[r][j + 1] = max(dp[r ^ 1][j + 1], dp[r][j]);
        return dp[m % 2][n];
    }
};

/**
 * convert LCS to LIS (Longest Increasing Subsequence)
 *  假设两个字符串 s1 = "abcadc", s2 = "cabedab"
 *  记录 s1 中的每个字符在 s2 中出现的位置，将位置降序排列，如
 *  index(a) = [5, 1], index(b) = [6, 2], index(c) = [0], index[d] = [4]
 *  按 s1 中每个字符的位置 用记录下的 index 替代排列形成一个 数字序列 nums = [5, 1, 6, 2, 0, 5, 1, 4, 0]
 *  对 nums 求 LIS 得到的长度就是 LCS(s1, s2) 的值（TODO:不懂，怎么证明？）
 * 
 * O(NlogN) 贪心 + 二分搜索 解决 LIS：
 *  用 lis[i] 记录 长度为 i+1 的LIS结尾元素的最小值，对于一个上升子序列，其结尾元素越小，越有利于在后面接其他的元素，也就越可能变得更长。
 *  对于每个 nums[i]， 如果 nums[i] > lis 的最后一个元素， 即 nums[i] 可以直接连到当前 LIS 后
 *                    反之，找到 lis 数组中第一个 大于等于 nums[i] 的位置，并用 nums[i] 更新之。可能更新替换掉整条 LIS
 *                    考虑 [11, 12, 5, 6, 7, 0, 1, 2, 3]， LIS 会被两次全部替换，从 [11,12] -> [5,6,7] -> [0,1,2,3]
 * 
 * Runtime: 8 ms, faster than 99.73%, 
 *      avg O(NlogN), worst O(MNlog(MN)) for "aaaaa" & "aaaaa" will construct large size nums to solve LIS, so better not too similar
 * Memory Usage: 7.1 MB, less than 100.00%, O(M*N) in worst
 * 
 * Reference:
 *  https://leetcode.com/problems/longest-common-subsequence/discuss/598697/no-DP-nlogn-solution-8ms
 *  https://www.cnblogs.com/KYSpring/p/9021909.html
 *  https://blog.csdn.net/George__Yu/article/details/75896330
 *  http://www.mamicode.com/info-detail-237214.html
*/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        // convert to LIS
        // record index in text2 for each exist char in text2
        unordered_map<char, vector<int>> index;
        for (int i = 0; i < n; ++i) {
            index[text2[i]].push_back(i);
        }
        // construct index vector from char in text1
        vector<int> nums;
        for (char c : text1) {
            vector<int>& tmp = index[c];
            for (int i = tmp.size()-1; i >= 0; --i) {
                nums.push_back(tmp[i]);
            }
        }
        if (nums.empty())
            return 0;
        // greedy and binarySearch solve LIS
        // lis[i] represents the minimum value of the last element for a LIS with length i+1
        vector<int> lis(1, nums[0]);
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > lis.back())
                // connect nums[i] to LIS directly
                lis.push_back(nums[i]);
            else {
                // update potential better LIS, maybe modify entire LIS
                // ex: 11, 12, 5, 6, 7, 0, 1, 2, 3
                int firstGE = binary_find_lower_bound(lis, nums[i]);
                lis[firstGE] = nums[i];
            }
        }
        return lis.size();
        
    }
private:
    // binary serach the index of first element that great or equal to given value
    // 可以用内置函数 iterator it = lower_bound(nums.begin(), nums.end(), value)
    int binary_find_lower_bound(const vector<int>& nums, int value) {
        int lo = 0, hi = nums.size() - 1, mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            // 中间值大于等于 value，第一个大于等于的一定是中间值或在左侧
            if (nums[mid] >= value)
                hi = mid;  // 不能 mid - 1
            else
                lo = mid + 1;
        }
        if (nums[hi] >= value)
            return hi;
        else
            return -1;
    }
};