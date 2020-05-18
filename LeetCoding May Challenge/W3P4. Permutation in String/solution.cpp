#include<string>
#include<vector>

using namespace std;

/**
 * Sliding Window
 * use alphabet vector as hash table recording occurence of short string
 *      a sub-problem of 438
 * Runtime: 12 ms, faster than 76.14%, O(N)
 * Memory Usage: 7.4 MB, less than 100.00%, O(1)
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int len1 = s1.size(), len2 = s2.size();
        if (len1 > len2)
            return false;
        const int alphabet = 26;
        // record chacter occurence in s1
        vector<int> hash(alphabet, 0);
        for (char c : s1)
            ++hash[c - 'a'];
        
        int count = s1.size(), start = 0, end = 0;
        while (end < len2) {
            // move end, decrease hash value
            // if current end char s2[end] still needed for meet permutation, decrease the count
            // hash value for end char > 0 means the char is needed for match p
            if (hash[s2[end++] - 'a']-- > 0)
                --count;
            // count == 0, a valid permutation found
            if (0 == count)
                return true;
            // window size equal to s2.size, need to slide
            if (end - start == len1) {
                // only when hash value of start char >= 0, the start char is exist and needed once in s1
                // now the start char is removed, count++
                if (hash[s2[start] - 'a'] >= 0)
                    ++count;
                // increase start and hash value
                ++hash[s2[start] - 'a'];
                ++start;
            }
        }
        return false;
    }
};
