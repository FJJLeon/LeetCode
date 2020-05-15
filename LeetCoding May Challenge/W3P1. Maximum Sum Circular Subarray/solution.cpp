#include<vector>
#include<limits.h>

using namespace std;

/**
 * use Kadane's Algorithm resolve N array
 * 
 * Runtime: TLE, O(N^2)
*/
class Solution1 {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int N = A.size();
        int maxSum = INT_MIN;
        for (int i = 0; i < N; ++i) {
            int sum = 0;
            for (int j = i; j < i + N; ++j) {
                sum = max(sum + A[j % N], A[j % N]);
                maxSum = max(maxSum, sum);
            }
        }
        return maxSum;
    }
};

/**
 * for splited circular subarray
 *  maxSubarray = Σ(A[0..i], A[j..N-1]) = Σ(A[0..N-1]) - Σ(A[i+1, j-1]) for certain i, j if exists
 * we can resolve **minSubarray** for a non-splited subarray instead
 * 
 * cannot think about *.*
 * 
 * Runtime: 164 ms, O(N)
 * Memory Usage: 40 MB, O(1)
*/
class Solution2 {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int total = 0;
        int maxSum = INT_MIN, curMax = 0;
        int minSum = INT_MAX, curMin = 0;
        for (int n : A) {
            // total sum
            total += n;
            // max subarray sum
            curMax = max(curMax + n, n);
            maxSum = max(maxSum, curMax);
            // min subarray sum
            curMin = min(curMin + n, n);
            minSum = min(minSum, curMin);
        }
        // all number is negative
        // under this situation, the min subarray is the whole array causing the corresponding max subarray empty, invalid
        if (maxSum < 0)
            return maxSum;
        return max(maxSum, total - minSum);
    }
};
