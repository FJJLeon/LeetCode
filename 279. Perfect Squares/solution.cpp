#include<math.h>
#include<vector>
#include<iostream>

using namespace std;

/**
 * DP
 * dp[n] = min(dp[1] + dp[n-1], dp[4] + dp[n-4], ...)
 * 
 * Runtime: 104 ms, faster than 73.30%, O(N*sqrt(N))
 * Memory Usage: 9 MB, less than 90.38%, O(N)
*/
class Solution11 {
public:
    int numSquares(int n) {
        int maxRoot = sqrt(n);
        vector<int> dp(n + 1, 0);
        // dp[perfect square] = 1
        for (int r = 1; r <= maxRoot; ++r)
            dp[r*r] = 1;
        
        for (int i = 2; i <= n; ++i) {
            if (dp[i] != 0)
                continue;
            int minNum = INT_MAX;
            int curRoot = sqrt(i);
            // for n=14, dp[9]+dp[5] dp[4]+dp[10] already include dp[1] + dp[13], big half is enough
            // loop all, Runtime: 216 ms
            for (int r = curRoot; r > curRoot/2; --r)
                minNum = min(minNum, dp[r*r] + dp[i-r*r]);
            dp[i] = minNum;
        }
        
        return dp[n];
    }
};

/**
 * static DP, it's a trick
 * there are hundreds of testcase, many results have been calculated in early testcase
 * store the dp result for later testcase to reduce runtime
 * 
 * Runtime: 4 ms, faster than 97.47%, O(N*sqrt(N))
 * Memory Usage: 6.2 MB, less than 100.00%, O(N)
*/
class Solution12 {
public:
    int numSquares(int n) {
        // mark dp as static so reused
        static vector<int> dp({0});
        // record old dp size, resize if enlarge needed
        int oldsize = dp.size();
        dp.resize(max(oldsize, n+1), 0);
        
        int maxRoot = sqrt(n);
        // dp[perfect square] = 1
        for (int r = sqrt(oldsize); r <= maxRoot; ++r)
            dp[r*r] = 1;
        // calculate from oldsize to n if needed
        for (int i = oldsize; i <= n; ++i) {
            if (dp[i] != 0)
                continue;
            int minNum = INT_MAX;
            int curRoot = sqrt(i);
            for (int r = curRoot; r > curRoot/2; --r)
                minNum = min(minNum, dp[r*r] + dp[i-r*r]);
            dp[i] = minNum;
        }
        
        return dp[n];
    }
};

/**
 * Math solution. Lagrange's Four Square theorem 拉格朗日四平方和定理:每个正整数都可以表示为至多4个正整数的平方和
 * 推论: 当且仅当 n = (4^a)(8b+7) a,b 为整数 时，n 才能表示成 4 个正整数的平方和
 * 另外：n 和 n/4（能整除）能被相同个数的正整数平方和表示
 * 
 * Runtime: 0 ms, faster than 100.00%, O(sqrt(N)), 跪了，向拉格朗日低头
 * Memory Usage: 6 MB, less than 100.00%, O(1)
*/
class Solution2 {
public:
    int numSquares(int n) {
        if (isSquare(n))
            return 1;
        
        while (0 == n & 3) // n % 4 == 0
            n >>= 2;       // n /= 4
        
        if (7 == n & 7)    // n % 8 == 7
            return 4;
        
        // check whether 2
        int maxRoot = sqrt(n);
        for (int r = maxRoot; r > maxRoot/2; --r) {
            if (isSquare(n - r*r))
                return 2;
        }
        // not 1,2,4
        return 3;
    }
private:
    bool isSquare(int n) {  
        int root = sqrt(n);  
        return root*root == n;  
    }
};
