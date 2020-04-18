#include<vector>

using namespace std;

/**
 * DP, m*n dp space maintained
 * 
 * Runtime: 8 ms, faster than 85.04%, O(M*N)
 * Memory Usage: 8.6 MB, less than 100.00%, O(M*N)
*/
class Solution11 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0)
            return 0;
        int n = grid[0].size();
        if (n == 0)
            return 0;
        vector<vector<int>> dp = vector<vector<int>>(m, vector<int>(n, 0));
        // origin
        dp[0][0] = grid[0][0];
        // first row
        for (int i = 1; i < m; ++i)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        // first column
        for (int j = 1; j < n; ++j)
            dp[0][j] = dp[0][j-1] + grid[0][j];
        // rest
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        
        return dp[m-1][n-1];
    }
};


/**
 * optimize space complexity
 * one row or column dp space is enough
 *      code as row, min(row, column) will be better
 * 
 * Runtime: 8 ms, faster than 85.04%, O(M*N)
 * Memory Usage: 8.1 MB, less than 100.00%, O(min(M, N))
*/
class Solution12 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0)
            return 0;
        int n = grid[0].size();
        if (n == 0)
            return 0;
        // one row dp space is enough
        vector<int> row = vector<int>(n, 0);
        // origin
        row[0] = grid[0][0];
        // first row
        for (int j = 1; j < n; ++j)
            row[j] = row[j-1] + grid[0][j];
        // rest
        for (int i = 1; i < m; ++i) {
            // next row
            row[0] += grid[i][0];
            for (int j = 1; j < n; ++j) {
                // row[j-1] is new left, row[j] is old up
                row[j] = min(row[j-1], row[j]) + grid[i][j];
            }
        }
        
        return row[n-1];
    }
};
