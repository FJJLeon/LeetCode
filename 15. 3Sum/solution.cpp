#include<vector>
#include<algorithm>

using namespace std;

/**
 * sort first, fix one (value as f) and binary search 2Sum with target = -f
 * 
 * Runtime: 92 ms, faster than 70.50%, O(N^2)
 * Memory Usage: 19.5 MB, less than 97.65%, O(1)
*/
class Solution11 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // sort first
        sort(nums.begin(), nums.end());
        int len = nums.size();

        vector<vector<int>> res;
        for (int i = 0; i < len-2; i++) {
            //skip duplicate
            // note: nums[i] == nums[i+1] is not right, may skip all
            if (i > 0 && nums[i] == nums[i-1])
                continue;
            int target = -nums[i];
            int left = i + 1, right = len - 1;
            while (left < right) {
                int tmp = nums[left] + nums[right];
                if (tmp == target) {
                    res.push_back(vector<int>({-target, nums[left], nums[right]}));
                    // skip duplicate and search next
                    while (left < right && nums[left] == nums[left+1])
                        left++;
                    while (left < right && nums[right] == nums[right-1])
                        right--;
                    left++;
                    right--;
                }
                else if (tmp < target)
                    left++;
                else
                    right--;
            }
        }
        
        return res;
    }
};


/**
 * simple optimization
 * we sort the nums at first, when we meet nums[i] > 0, all numbers after it > 0 -> impossible , early stop
*/
class Solution12 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // sort first
        sort(nums.begin(), nums.end());
        int len = nums.size();
        //cout << len;
        vector<vector<int>> res;
        for (int i=0; i<len-2; i++) {
            // simple optimization
            if (nums[i] > 0)
                break;
            //skip duplicate
            // note: nums[i] == nums[i+1] is not right, may skip all
            if (i>0 && nums[i] == nums[i-1])
                continue;
            int target = -nums[i];
            int left = i+1, right = len-1;
            while (left < right) {
                int tmp = nums[left] + nums[right];
                if (tmp == target) {
                    res.push_back(vector<int>({-target, nums[left], nums[right]}));
                    // skip duplicate and search next
                    while (left < right && nums[left] == nums[left+1])
                        left++;
                    while (left < right && nums[right] == nums[right-1])
                        right--;
                    left++;right--;
                }
                else if (tmp < target)
                    left++;
                else
                    right--;
            }
        }
        
        return res;
    }
};