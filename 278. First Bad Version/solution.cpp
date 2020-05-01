// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

extern bool isBadVersion(int version);

/**
 * Binary Search
 * 类似在升序序列中找到第一个大于等于 n 的索引
 * 
 * Runtime: 0 ms， O(logN)
 * Memory Usage: 6 MB, O(1)
*/
class Solution {
public:
    int firstBadVersion(int n) {
        int lo = 1, hi = n, mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (isBadVersion(mid))
                hi = mid;   // mid may be the target, cannot be mid - 1
            else
                lo = mid + 1;
        }
        return hi;
    }
};