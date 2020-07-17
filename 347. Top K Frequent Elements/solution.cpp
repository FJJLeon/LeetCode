#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;


/**
 * bucket sort
 * use map record frequent of each number
 * use bucket idea, number frequent as bucket index
 * 
 * Runtime: 44 ms, faster than 45.30%, O(N) (?)
 * Memory Usage: 14.2 MB, less than 24.25%, O(M) m for count of unique number
*/
class Solution11 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // use map record frequent of each number, O(N) ? no hash collision
        unordered_map<int, int> freq;
        int maxFreq = 0;
        for (int &n : nums) {
            freq[n]++;
            maxFreq = max(maxFreq, freq[n]);
        }
        // insert each unique number to bucket, frequent as index, O(M)
        vector<vector<int>> bucket(maxFreq + 1);
        for (auto &p : freq)
            bucket[p.second].push_back(p.first);
        // get top k frequent unique number, O(K)
        vector<int> res;
        for (int f = maxFreq; f > 0; --f) {
            for (int &n : bucket[f]) {
                res.push_back(n);
            }
            /**
            as Note said, "the answer is unique", so the same bucket elem must be all taken
            res.insert(res.end(), bucket[f].begin(), bucket[f].end());  // is ok
            */
            if (res.size() == k)
                break;
        }
        return res;
    }
};