#include<vector>

/**
 * DP
 * dp[N]: num of BST for [1..N]
 * F(i, N): num of BST for [1..N] as data, i as root  
 * 
 * F(i, N) = dp[i - 1] * dp[N - i]
 *      ex: F(3, 5) = dp[2] * dp[2], 3 as root, [1,2] as left sub-BST, [4,5] as right sub-BST
 * 
 * dp[0] and dp[1] default to 1
 * dp[2] = dp[0] * dp[1] + dp[1] * dp[0]
 * dp[3] = dp[0] * dp[2] + dp[1] * dp[1] + dp[2] * dp[0]
 * ...
 * dp[N] = ∑F(i, N), i in [1, N]
 * 
 * Runtime: 0 ms, faster than 100.00%, O(N^2)
 * Memory Usage: 6 MB, less than 83.27%, O(N)
*/
class Solution1 {
public:
    int numTrees(int n) {
        std::vector<int> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int r = 1; r <= i; ++r) {
                dp[i] += dp[r - 1] * dp[i - r];
            }
        }
        return dp[n];
    }
};

/**
 * Catalan Number
 * https://en.wikipedia.org/wiki/Catalan_number
 * 
 * dp expression meet the definition of Catalan Number
 * recursive expression: dp[N] = dp[N-1] * (4*N - 2) / (N + 1)
 * solution: dp[N] = C(2N, N) - C(2N, N+1) = C(2N, N) / (N+1)
 * C(2N, N) = [N+1 * N+2 *...* 2N-1 * 2N] / [1 * 2 *...* N-1 * N]
 * 
 * Runtime: O(N) ?
 * Memory Usage: O(1)
*/
class Solution2 {
public:
    int numTrees(int n) {
        double res = 1;
        for (int i = 1; i <= n; ++i) {
            res = res * (n+i) / i;
        }
        return (int)(res/(n+1));
    }
};
