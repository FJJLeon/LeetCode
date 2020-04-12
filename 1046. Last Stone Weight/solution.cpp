#include<vector>
#include<queue>

using namespace std;

/**
 * use priority queue simulate the process
 * 
 * Runtime: 0 ms, O(NlogN)
 * Memory Usage: 6.2 MB, O(N)
*/
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // construct priority queue, default high priority first
        priority_queue<int> pq(stones.begin(), stones.end());
        
        while (pq.size() > 1) {
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();
            
            if (x != y) { // x >= y
                pq.push(x - y);
            }
        }
        
        return pq.empty() ? 0 : pq.top();
    }
};
