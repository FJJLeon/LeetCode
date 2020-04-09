#include<string>
#include<iostream>

using namespace std;

/**
 * Linear space solution is easy to be thought, constant is not
 * If we traverse from begin to end, we cannot know whether one character will be backspaced. 
 * However, if traverse from end to begin we can always know that.
 * 
 * Runtime: 0 ms, O(N)
 * Memory Usage: 6.2 MB, O(1)
*/
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1, j = T.size() - 1;
        // count of backspace
        int cs = 0, ct = 0;
        // one string (S or T) has remaining character
        while (i >= 0 || j >= 0) {
            // skip all backspaced character for S
            while (i >= 0 && (S[i] == '#' || cs)) {
                cs += S[i] == '#' ? 1 : -1;
                --i;
            }
            // skip all backspaced character for T
            while (j >= 0 && (T[j] == '#' || ct)) {
                ct += T[j] == '#' ? 1 : -1;
                --j;
            }
            // check really typed char
            if (i >= 0 && j >= 0 && S[i] != T[j])
                return false;
            // one string remaining while another one over
            if ( (i >= 0) != (j >= 0) )
                return false;
            --i;
            --j;
        }
        // all check passed, two typed strings is equal
        return true;
    }
};
