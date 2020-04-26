#include<string>
#include<vector>

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
 * todo: convert to LIS
 * 
 * Runtime: O(M*logN)
*/