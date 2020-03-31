#include<vector>

using namespace std;

/**
 * Dutch national flag problem
 * Three-way partition
 * 
 *              [ red )[ white )[ unclassified )[ blue ]
 *                    i        j               k
 * 
 * keep three pointer, i for top of red, j for top of white, k for bottom of blue
 * element at j is to be sorted, if the elem is red, swap it with elem of i, move forward i and j
 *                               if the elem is white, leave it
 *                               if the elem is blue, swap it with  elem of k (last unclassified elem), move backward k
 * 
 * Runtime: 0 ms, faster than 100.00%, O(N)
 * Memory Usage: 6.3 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    const int red = 0, white = 1, blue = 2;
    
    void sortColors(vector<int>& nums) {

        int i = 0, j = 0, k = nums.size() - 1;
        while (j <= k) {
            if (nums[j] == red) {
                swap(nums[i], nums[j]);
                ++i;
                ++j;
            }
            else if (nums[j] == white) {
                ++j;
            }
            else {
                swap(nums[j], nums[k]);
                --k;
            }
        }
    }
};
