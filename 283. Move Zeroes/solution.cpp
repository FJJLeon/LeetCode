#include<vector>

using namespace std;

/**
 * my two pointer
 *  1. find zero elem
 *  2. find non-zero elem after 1.'s index
 *  3. swap
 *  4. back 1
 * 
 * Runtime: 12 ms, faster than 94.78%, O(N), though nested loop, but each pointer(z, nz) only one pass
 * Memory Usage: 7.1 MB, less than 100.00%, O(1)
*/
class Solution11 {
public:
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        // z - zero, nz - non-zero
        for (int z = 0, nz = 0; z < len; ++z) {
            if (nums[z] == 0) {
                // search less
                nz = max(z, nz) + 1;
                // find nearest non-zero
                while (nz < len && nums[nz] == 0)
                    ++nz;
                if (nz < len)
                    swap(nums[z], nums[nz]);
                else
                    break;
            }
        }       
    }
};

/**
 * elegant two pointer
 *  0. pos for store incoming non-zero elem
 *  1. find non-zero
 *  2. swap non-zero with pos, pos++
 *  3. back 1
 * 
*/
class Solution12 {
public:
    void moveZeroes(vector<int>& nums) {
        for (int pos = 0, i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                // swap non-zero with correct position
                if (i != pos) {
                    swap(nums[pos], nums[i]);
                }
                ++pos;
            }
        }
    }
};

/**
 * 1. move all non-zero forward
 * 2. fullfill zero after
 * NO swap
 * 
 * Runtime: 12 ms, faster than 94.78%
 * Memory Usage: 7.1 MB, less than 100.00%
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int pos = 0, len = nums.size();
        // move forward all non-zero
        for (int i = 0; i < len; ++i) {
            if(nums[i] != 0){
                nums[pos++] = nums[i];
            }
        }
        // fullfill zero
        while(pos < len){
            nums[pos++] = 0;
        }
    }
};
