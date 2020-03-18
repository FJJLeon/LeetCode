#include<string>
#include<vector>

using namespace std;

/**
 * Problem means t is one char longer than s, and t is out of order with (s + target char)
 * 
 * use only one vector record char number, from s --, t ++, then the one number not equal to zero is difference
 * 
 * Runtime: 4 ms, faster than 82.49%
 * Memory Usage: 8.1 MB, less than 100.00%
*/
class Solution1 {
public:
    char findTheDifference(string s, string t) {
        const int numOfLow = 26;
        vector<int> charNum(numOfLow);
        charNum[t.back()-'a'] = 1;
        
        for (int i=0; i<s.length(); ++i) {
            --charNum[s[i]-'a'];
            ++charNum[t[i]-'a'];
        }
        for (int i=0; i<numOfLow; i++) {
            if (charNum[i] != 0)
                return 'a'+i;
        }
        return 0;
    }
};

/**
 * Awesome solution with XOR
 * make xor manipulation to each char of s and t, and the result is difference
 * 
 * Runtime: 0 ms, faster than 100.00%
 * Memory Usage: 7.9 MB, less than 100.00%
*/
class Solution2 {
public:
    char findTheDifference(string s, string t) {
        char res = t.back();
        
        for (int i=0; i<s.length(); ++i) {
            res ^= s[i] ^ t[i];
        }
        
        return res;
    }
};