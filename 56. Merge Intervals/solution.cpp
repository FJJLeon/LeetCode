#include<vector>
#include<algorithm>

using namespace std;

/**
 * sort then linear scan
 * 
 * Runtime: 16 ms, faster than 93.86%
 * Memory Usage: 11.7 MB, less than 100.00%
*/
class Solution11 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        int len = intervals.size();
        if (len == 0)
            return res;
        
        sort(intervals.begin(), intervals.end(), compare);
        
        vector<int> s{intervals[0][0], intervals[0][1]};
        for (int i=1; i<len; ++i) {
            // current interval non-overlap with previous
            if (intervals[i][0] > s[1]) {
                res.push_back(vector<int>{s[0], s[1]});
                s[0] = intervals[i][0];
                s[1] = intervals[i][1];
            } else {
                s[1] = max(intervals[i][1], s[1]);
            }
        }
        res.push_back(vector<int>{s[0], s[1]});
        
        return res;
    }
private:
    typedef vector<int> interval;
    // note static is necessary (TODO: why)
    static bool compare(const interval &i1, const interval &i2) {
        return i1[0] < i2[0];
    }
};

/**
 * refactor
 * 
 * use lambda expression for cmp
 * push and merge interval directly in result vector
 * 
 * Runtime: 16 ms, faster than 93.99%
 * Memory Usage: 11.6 MB, less than 100.00%
*/
class Solution12 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1)
            return intervals;
        // lambda for cmp
        sort(intervals.begin(), intervals.end(), [](const interval& i1, const interval& i2){
            return i1[0] < i2[0];
        });
        
        vector<vector<int>> res;
        for (auto& ci : intervals) {
            // current interval overlap with previous, merge
            if (!res.empty() && res.back()[1] >= ci[0]) {
                res.back()[1] = max(res.back()[1], ci[1]);
            } 
            // non-overlap, new interval pushed to res
            else {
                res.push_back(ci);
            }
        }
        
        return res;
    }
private:
    typedef vector<int> interval;
};