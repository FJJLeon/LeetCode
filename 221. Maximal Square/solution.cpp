#include<vector>
#include<iostream>

using namespace std;

/**
 * Brute Force, 这个DP自己想不出哦
 * for each matrix position with value = '1', find largest square with this position as left upper vertex
 * record max side length and current side length
 * 
 * Runtime: 24 ms, faster than 33.76%, O((MN)^2)
 * Memory Usage: 8.4 MB, less than 100.00%, O(1)
*/
class Solution1 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if ((m = matrix.size()) == 0)
            return 0;
        if ((n = matrix[0].size()) == 0)
            return 0;
        int maxL = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '0')
                    continue;
                bool allOne = true;
                int l;
                // judge current length > max length
                for (l = 1; l <= maxL; ++l) {
                    if (!allOneExpand(matrix, i, j, l)) {
                        allOne = false;
                        break;
                    }
                }
                if (!allOne)
                    continue;
                // expand and update max length if all '1' in expanded edge
                while (i + l <= m && j + l <= n) {
                    if (allOneExpand(matrix, i, j, l))
                        maxL = l;
                    else 
                        break;
                    l++;
                }
            }
        }
        return maxL * maxL;
    }
private:
    int m, n;
    // for matrix index (x, y) and square length 'l'
    // there is a square with this index as upper left vertex and l as length
    // judge whether the bottom row and right column is all '1'
    bool allOneExpand(vector<vector<char>>& matrix, int x, int y, int l) {
        if (x + l > m || y + l > n)
            return false;
        // judge bottom row
        for (int j = y; j < y + l; ++j) {
            if (matrix[x + l - 1][j] != '1')
                return false;
        }
        // judge right col
        for (int i = x; i < x + l; ++i) {
            if (matrix[i][y + l - 1] != '1')
                return false;
        }
        return true;
    }
};

/**
 * DP
 * maintain same dimensions dp matrix
 * dp[i][j] represent the side length of square with matrix[i][j] as **bottom right** vertex (从左上开始遍历，DP 能利用的肯定是左上数据，所以要作为右下顶点)
 * dp state transition equation, dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1 for matrix[i][j] is '1'
 *      一个点的左上邻接三个点，取三者的最小值 min，则该点可以形成的最大正方形边长为 min + 1
 * 
 * Runtime: 12 ms, faster than 98.69%， O(MN)
 * Memory Usage: 8.8 MB, less than 100.00%, O(MN)
*/
class Solution21 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;
        int m = matrix.size(), n = matrix[0].size();
        // extra row and col for 0
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); 
        int maxl = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (matrix[i-1][j-1] != '1')
                    continue;
                dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                maxl = max(maxl, dp[i][j]);
            }
        }
        return maxl * maxl;
    }
};
/**
 * memory optimization DP
 * each state transition equation only utilizes the last row
 * one row space is enough
 * 
 *          prevLU   dp[j]               dp[i-1][j-1]  dp[i-1][j]
 *          dp[j-1]  new_dp[j]    <---   dp[i][j-1]    dp[i][j]
 * 
 * Runtime: 20 ms, faster than 77.85%, O(MN)
 * Memory Usage: 8.3 MB, less than 100.00%, O(N)
*/
class Solution22 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;
        int m = matrix.size(), n = matrix[0].size();
        // only one row dp vector necessary
        vector<int> dp(n + 1, 0);
        int maxl = 0;
        int prevLeftUpper = dp[0];
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // record previous left upper dp value for next state
                int tmp = dp[j];
                if (matrix[i-1][j-1] == '1') {
                    dp[j] = min(min(dp[j], dp[j-1]), prevLeftUpper) + 1;
                    maxl = max(maxl, dp[j]);
                }
                else {
                    // set to 0 if no square
                    dp[j] = 0;
                }
                prevLeftUpper = tmp;
            }
        }
        return maxl * maxl;
    }
};


int main() {
    vector<vector<char>> m = {
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    };
    cout << Solution1().maximalSquare(m) << endl; // 16
}