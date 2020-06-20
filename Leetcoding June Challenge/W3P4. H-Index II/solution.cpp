#include<vector>

using namespace std;

/**
 * binary search
 * example:
 * 0 1 3 5 6  citation
 * 0 1 2 3 4  origin index of array (index0)
 * 5 4 3 2 1  size - origin index   (index1)
 *            which means the number of paper whose citation >= this citation
 * find the first item whose citation >= index1
 * for this example, citation[2] = 3 and 3 >= 3(index1) is the result
 * 
 * Runtime: 44 ms, O(logN)
 * Memory Usage: 18.7 MB, O(1)
*/
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int size = citations.size();
        if (size == 0)
            return 0;
        int lo = 0, hi = size - 1, mid;
        // binary search, find first elem >= size - index
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (citations[mid] == size - mid)
                return size - mid;
            else if (citations[mid] < size - mid)
                lo = mid + 1;
            else
                hi = mid;
        }
        
        return citations[lo] >= size - lo ? size - lo : 0;
    }
};
