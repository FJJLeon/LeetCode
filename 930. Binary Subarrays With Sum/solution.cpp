#include<vector>
#include<unordered_map>

using namespace std;

/**
 * Sliding Window
 * expand window to make sum of subarray[i, jl) equal to S
 * continue expand to find jh that subarray[jl, jh) all zeros
 * so there are 'jh-jl+1' valid subarray
 * However, it cannot handle S=0
 * 
 * Runtime: 28 ms, faster than 75.19%, O(N)
 * Memory Usage: 9 MB, less than 100.00%, O(1)
*/
class Solution11 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if (S == 0)
            return helper0(A);
        
        int jl = 0, jh = 0, len = A.size();
        int count = 0, sum = 0;
        for (int i=0; i<len; ++i) {
            // expand window [i,jl) until sum equal targer S
            while (jl < len && sum < S) {
                sum += A[jl++];
            }
            // find jh that [jl, jh) all zeros
            jh = jl;
            while (jh < len && A[jh] == 0) {
                ++jh;
            }
            // if sum equal S, there are 'jh-jl+1' valid subarray
            if (sum == S) {
                count += jh - jl + 1;
            }
            // shrink window by moving forward i
            sum -= A[i];
        }
        
        return count;
    }
private:
    // S=0 handled separately
    int helper0(vector<int>& A) {
        int count0 = 0, res = 0;
        for (int i=0; i<A.size(); ++i) {
            if (A[i] == 0) {
                count0++;
            }
            else {
                res += (count0+1)*count0/2;
                count0 = 0;
            }
        }
        res += (count0+1)*count0/2;
        return res;
    }
};


/**
 * optimize S11
 * mark end index(j) of window fixed and shrink window to make sum equal S
 * but move start index to find all valid subarray, it handle S=0 (TODO:but why)
 * 
 * Runtime: 28 ms, faster than 75.19%
 * Memory Usage: 8.8 MB, less than 100.00%
*/
class Solution12 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int il = 0, ih = 0, len = A.size();
        int count = 0, sum = 0;
        for (int j=0; j<len; ++j) {
            // window ended at j
            sum += A[j];
            // shrink window [il, j] until sum equal targer S
            while (il < j && sum > S) {
                sum -= A[il++];
            }
            // find ih that [il, ih] all zeros
            ih = il;
            while (ih < j && A[ih] == 0) {
                ++ih;
            }
            // if sum equal S, there are 'ih-il+1' valid subarray
            if (sum == S) {
                count += ih - il + 1;
            }
        }
        
        return count;
    }
};


/**
 * Prefix Sum
 * 
 * Runtime: 72 ms, faster than 14.32%, O(N)
 * Memory Usage: 17.5 MB, less than 20.00%, O(N)
*/
class Solution2 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int len = A.size();
        // key: prefixSum, value: count of the prefixSum
        unordered_map<int, int> count({{0, 1}});
        int preSum = 0, res = 0;
        for (int a : A) {
            preSum += a;
            res += count[preSum - S];
            count[preSum]++;
        }
        return res;
    }
};