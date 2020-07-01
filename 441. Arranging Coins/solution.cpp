#include<math.h>

using namespace std;

/**
 * math 
 * 
 * (1+r)*r/2 = n
 * r^2 + r -2n = 0
 * r = (-1 + sqrt(1+8n))/2
 * 向下取整
 * 
 * Runtime: 0 ms, faster than 100.00%, O(1)
 * Memory Usage: 5.9 MB, less than 90.20%, O(1)
*/
class Solution1 {
public:
    int arrangeCoins(int n) {
        return (int)((-1 + sqrt(1+8*(long)n)) / 2);     
    }
};


/**
 * binary search
 * 
 * find the biggest r, thar r(1+r)/2 <= n
 * 
 * Runtime: 4 ms, faster than 79.21%, O(log(sqrt(n)))
 * Memory Usage: 6 MB, less than 42.09%, O(1)
*/
class Solution2 {
public:
    int arrangeCoins(int n) {
        int lo = 0, hi = sqrt(2)*sqrt(n);
        long mid, count;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            count = mid*(1+mid)/2;
            if (count == n)
                return mid;
            else if (count <= n)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return hi;
    }
};


/**
 * BF
 * 
 * Runtime: 12 ms, faster than 25.89%,O(sqrt(n))
 * Memory Usage: 5.9 MB, less than 63.94%<,O(1)
*/
class Solution3 {
public:
    int arrangeCoins(int n) {
        int stage = 0;
        while (n >= stage) {
            n -= stage;
            ++stage;
        }
        
        return stage - 1;
    }
};