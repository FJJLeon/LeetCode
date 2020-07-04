#include<vector>
#include<math.h>

/**
 * DP, merge sort for ascending array
 * 
 * basing ugly[0] = 1
 * all ugly number is product of ugly number previous with 2 or 3 or 5
 * three-way merge for arrays below
 *  1x2, 2x2, 3x2, ...
 *  1x3, 2x3, 3x3, ...
 *  1x5, 2x5, 3x5, ...
 * note:
 *  there are equal number between different factor array
 *  thus every factor array need be checked for each iteration
 * 
 * Runtime: 8 ms, faster than 85.97%, O(N)
 * Memory Usage: 7.7 MB, less than 69.36%, O(N)
*/
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        std::vector<int> dp(n);
        dp[0] = 1;
        int i2 = 0, i3 = 0, i5 = 0;
        for (int i = 1; i < n; ++i) {
            dp[i] = std::min(std::min(dp[i2]*2, dp[i3]*3), dp[i5]*5);
            // every factor array need be checked for each iteration, equal number exists
            if (dp[i] == dp[i2]*2)
                ++i2;
            if (dp[i] == dp[i3]*3)
                ++i3;
            if (dp[i] == dp[i5]*5)
                ++i5;
        }
        return dp[n-1];
    }
};
