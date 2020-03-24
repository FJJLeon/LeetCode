#include<string>

using namespace std;

/**
 * 
 * Runtime: 0 ms, faster than 100%
 * Memory Usage: 6.3 MB, less than 100.00%
*/
class Solution {
public:
    bool detectCapitalUse(string word) {
        if (isupper(word[0])) {
            return isSuffixAllLow(word, 1) || isSuffixAllUpp(word, 1);
        }
        else {
            return isSuffixAllLow(word, 1);
        }
    }
private:
    bool isSuffixAllLow(string w, size_t p) {
        if (p >= w.size())
            return true;
        for (int i=p; i<w.size(); ++i) {
            if (w[i] >= 'A' && w[i] <= 'Z')
                return false;
        }
        return true;
    }
    
    bool isSuffixAllUpp(string w, size_t p) {
        if (p >= w.size())
            return true;
        for (int i=p; i<w.size(); ++i) {
            if (w[i] >= 'a' && w[i] <= 'z')
                return false;
        }
        return true;
    }
};