#include<string>
#include<vector>

using namespace std;

/**
 * traverse backwards
 * 1. store last occurrence index of each letter
 * 2. if first appear, add to candidate, else remove from candidate
 * 3. traverse candidate and find the first unique
 * 
 * Runtime: 56 ms, faster than 63.45%, 
 *      Worse case like "abcde..xyz", need traverse input string one-pass and lowercase alphabet one-pass, better time complexity for long string than sol12
 * Memory Usage: 10.5 MB, less than 100.00%, O(1)
*/
class Solution11 {
public:
    int firstUniqChar(string s) {
        int len = s.size();
        if (len == 0)
            return -1;
        // store the last occurrence index of each letter
        vector<int> lastAppear(26, -1);
        // store only index of candidate letter, INT_MAX for not candidate, (maybe set is better)
        vector<int> candidate(26, INT_MAX);
        for (int i = len - 1; i >= 0; --i) {
            char c = s[i];
            // first appear, add to candidate
            if (lastAppear[c - 'a'] == -1) {
                lastAppear[c - 'a'] = i;
                candidate[c - 'a'] = i;
            }
            // repeated, remove from candidate
            else {
                candidate[c - 'a'] = INT_MAX;
            }
        }
        // traverse all candidate, res == INT_MAX for no candidate
        int res = INT_MAX;
        for (auto n : candidate)
            if (n != INT_MAX)
                res = min(res, n);
        
        return res == INT_MAX ? -1 : res;
    }
};
/**
 * traverse two-pass
 * 1. count occurrence number of each letter
 * 2. find first letter that appear only once
 * 
 * Runtime: 60 ms, faster than 61.35%, 
 *      Worst case like "aabbccdd...yyz", need traverse input string two-pass
 * Memory Usage: 10.6 MB, less than 100.00%, O(1)
*/
class Solution12 {
public:
    int firstUniqChar(string s) {
        int len = s.size();
        if (len == 0)
            return -1;
        vector<int> countAppear(26, 0);
        for (int i = 0; i < len; ++i) {
            ++countAppear[s[i] - 'a'];
        }
        for (int i = 0; i < len; ++i) {
            if (countAppear[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
};
