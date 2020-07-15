#include<string>

using namespace std;


/**
 * reverse whole string, then reverse each word
 * 
 * Runtime: 40 ms, faster than 12.37%
 * Memory Usage: 116.1 MB, less than 9.86%
 * 
 * u1s1, too much string memory allocate and copy, optimization required
*/
class Solution1 {
private:
    string reverseString(string s,int i, int j) {
        int l = i, r = j;
        while (l < r) {
            swap(s[l++], s[r--]);
        }
        return s.substr(i, j-i+1);
    }

public:
    string reverseWords(string s) {
        string res;
        int l = 0, r, len = s.size();
        // reverse whole string
        s = reverseString(s, 0, len - 1);
        // reverse each word
        while (l < len) {
            while (l < len && s[l] == ' ')
                ++l;
            if (l == len)
                break;
            r = l;
            while (r < len && s[r] != ' ')
                ++r;
            // reverse word s[l,r-1]
            res += reverseString(s, l, r - 1) + ' ';
            l = r + 1;
        }
        // move trailing space
        return res.substr(0, res.size() - 1);
    }
};
