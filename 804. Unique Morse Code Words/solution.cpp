#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

/**
 * 
 * Runtime: 0 ms, faster than 100%, O(Σlen(wi))
 * Memory Usage: 6.7 MB, less than 100.00%
*/
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morseCode = {".-","-...","-.-.","-..",".","..-.","--.",
                                 "....","..",".---","-.-",".-..","--","-.",
                                 "---",".--.","--.-",".-.","...","-","..-",
                                 "...-",".--","-..-","-.--","--.."};
        unordered_set<string> transf;
        
        for (string& w : words) {
            string s = "";
            for (char& c : w)
                s.append(morseCode[c - 'a']);
            transf.insert(s);
        }
        
        return transf.size();        
    }
};