#include<vector>
#include<queue>
#include<set>

using namespace std;


/**
 * pq store top3
 * set remove duplicate
 * 
 * Runtime: 28 ms, faster than 6.54%
 * Memory Usage: 8.2 MB, less than 100.00%
*/
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int> > q;
        set<int> s;
        for (auto n : nums) {
            if (s.find(n) == s.end()) {
                s.insert(n);
                
                q.push(n);
                if (q.size() > 3)
                    q.pop();
            }
        }
        
        if (q.size() == 2)
            q.pop();
        return q.top();
    }
};

/**
 * set is ordered
 * 
 * Runtime: 12 ms, faster than 36.55%
 * Memory Usage: 8.5 MB, less than 100.00%
*/
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> top3;
        for (int num : nums) {
            top3.insert(num);
            if (top3.size() > 3)
                top3.erase(top3.begin());
        }
        return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
    }
};