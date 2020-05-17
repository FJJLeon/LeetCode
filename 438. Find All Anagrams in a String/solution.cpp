#include<string>
#include<vector>

using namespace std;

/**
 * Sliding Window
 * use alphabet vector as hash table recording occurence
 * 
 * Runtime: 44 ms, faster than 45.89%, O(N), N=s.size
 * Memory Usage: 8.7 MB, less than 100.00%， O(1)
*/
class Solution1 {
public:
    vector<int> findAnagrams(string s, string p) {
        int slen = s.size(), plen = p.size();
        const int alphabet = 26;
        // record chacter occurence in p
        vector<int> anagram(alphabet, 0);
        for (char c : p)
            ++anagram[c - 'a'];
        // sliding window start point
        int start = 0;
        vector<int> tmp(alphabet, 0), res;
        // enlarge window to p.size()
        for(int j = 0; j < plen && start + j < slen; ++j)
            ++tmp[s[start+j] - 'a'];
        // check first window
        if (tmp == anagram)
            res.push_back(start);
        // sliding window step by step
        while (start + plen < slen) {
            --tmp[s[start] - 'a'];
            ++tmp[s[start+plen] - 'a'];
            ++start;
            if (tmp == anagram) // vector compare, O(26) = O(1)
                res.push_back(start);
        }
        return res;
    }
};

/**
 * Instead compare hash vector
 * use a count to mark a valid anagram
 * 
 * Runtime: 24 ms, faster than 91.54%, O(N)
 * Memory Usage: 8.4 MB, less than 100.00%
*/
class Solution2 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int slen = s.size(), plen = p.size();
        if (slen == 0 || plen == 0 || slen < plen)
            return res;
        const int alphabet = 26;
        // record chacter occurence in p
        vector<int> hash(alphabet, 0);
        for (char c : p)
            ++hash[c - 'a'];
        
        int count = p.size(), start = 0, end = 0;
        while (end < slen) {
            // move end, decrease hash value
            // if current end char s[end] still needed for anagram, decrease the count
            // hash value for end char > 0 means the char is needed for match p
            if (hash[s[end++] - 'a']-- > 0)
                --count;
            // count == 0, a valid anagram found
            if (0 == count)
                res.push_back(start);
            // window size equal to p.size, need to slide
            if (end - start == plen) {
                // only when hash value of start char >= 0, the start char is needed once (when start is once end)
                // now the start char is removed, count++
                if (hash[s[start] - 'a'] >= 0)
                    ++count;
                // increase start and hash value
                ++hash[s[start] - 'a'];
                ++start;
            }
        }
        return res;
    }
};
