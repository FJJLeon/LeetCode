#include<vector>
#include<algorithm>

using namespace std;

/**
 * sort and compare
 * 
 * after sort in ascending order, minAbsDiff must appear in two consecutive elements
 * 
 * Runtime: 172 ms, faster than 11.41%, O(NlogN)
 * Memory Usage: 15 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int minDiff = INT_MAX;
        vector<vector<int>> res;
        for (int i=1; i<arr.size(); ++i) {
            // new minDiff, clear res
            if (arr[i] - arr[i-1] < minDiff) {
                minDiff = arr[i] - arr[i-1];
                res = {{arr[i-1], arr[i]}};
            }
            // same minDiff, push
            else if (arr[i] - arr[i-1] == minDiff) {
                res.push_back({arr[i-1], arr[i]});
            }
        }
        return res;
    }
};