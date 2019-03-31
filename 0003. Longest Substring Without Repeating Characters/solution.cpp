#include <string>
using namespace std;

// my solution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxWin = 0;
        int begin = 0, end = 0;
        int len = s.length();
        string::size_type pos;
        for (int i = 0; i < len; i++) {
            // find s[i] in current window
            pos = s.substr(begin, end - begin).find(s[i]);
            //cout << begin << "-" << end << ":" << s.substr(begin, end - begin) << " find " << s[i] << " at " << pos << endl;
            // if found, window need shrink
            if (pos != s.npos) {
                begin = begin + pos + 1;
            }
            // update end pos and max window size if needed
            end++;
            int curWin = end - begin;
            if (curWin > maxWin)
                maxWin = curWin;
            
            //cout << "update:" << begin << end << maxWin << endl;
        }
        return maxWin;
    }
};

// Standard solution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxWin = 0;
        int len = s.length();
        int index[128] = {0};
        // i for begin of window, j for end
        for (int i = 0, j = 0; j < len; j++) {
            // if s[j] index in current window exist, duplicate occur
            // the index should >= i, window shrink
            i = max(i, index[s[j]]);
            // update index
            // note: index should be the pos of next char in string, will be assigned to i
            index[s[j]] = j + 1;
            // update max window size
            maxWin = max(j - i + 1, maxWin);
        }
            
        return maxWin;
    }
};