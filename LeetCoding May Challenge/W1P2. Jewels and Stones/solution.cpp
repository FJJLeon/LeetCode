#include<unordered_set>

using namespace std;

/**
 * 
 * Runtime: 4 ms, O(NlogM), M = J.size, N = S.size
 * Memory Usage: 6.4 MB, O(M)
*/
class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char> jewel(J.begin(), J.end());
        int res = 0;
        for (char c : S) {
            if (jewel.find(c) != jewel.end())
                ++res;
        }
        return res;
    }
};
