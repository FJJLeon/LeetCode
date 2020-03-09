#include<vector>
#include<unordered_map>

using namespace std;

/**
 * Hash Map
 * 
 * Runtime: 20 ms, 80.44%, O(N)
 * Memory Usage: 10.3 MB, 100.00%, O(N)
*/
class Solution1 {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        int len = nums.size();
        for (int el : nums) {
            if (++count[el] > len/2)
                return el;
        }
        // won't reach
        return -1;
    }
};

/**
 * Boyer-Moore Vote Algorithm
 * 
 * 对于数组中每一个元素，首先判断count是否为0，若为0，则把candidate设置为当前元素
 * 否则判断candidate是否与当前元素相等，若相等则count+=1，否则count-=1。
 * 同时去掉一个 多数 和一个 非多数，数组的多数不变
 * 
 * Reference:
 * https://apps.dtic.mil/dtic/tr/fulltext/u2/a131702.pdf
 * https://blog.csdn.net/kimixuchen/article/details/52787307
 * 
 * Runtime: 16 ms, 96.97%, O(N)
 * Memory Usage: 10.1 MB, 100.00%, O(1)
*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0, candidate = 0;
        int len = nums.size();
        for (int el : nums) {
            if (count == 0) {
                candidate = el;
                count = 1;
            } else {
                count += (el == candidate) ? 1 : -1;
            }
        }
        
        return candidate;
    }
};