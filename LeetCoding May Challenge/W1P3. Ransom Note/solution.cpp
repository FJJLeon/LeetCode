#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

/**
 * unordered_map
 * 
 * Runtime: 80 ms, O(M+N)
 * Memory Usage: 9 MB, O(26) = O(1)
*/
class Solution11 {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> countMag;
        for (char c : magazine) {
            ++countMag[c];
        }
        for (char c : ransomNote) {
            --countMag[c];
            if (countMag[c] < 0)
                return false;
        }
        return true;
    }
};
/**
 * replace with vector for there are only 26 lowercase letter
 * 
 * Runtime: 44 ms, O(M+N)
 * Memory Usage: 8.7 MB, O(1)
*/
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> countMag(26, 0);
        for (char c : magazine) {
            ++countMag[c - 'a'];
        }
        for (char c : ransomNote) {
            --countMag[c - 'a'];
            if (countMag[c - 'a'] < 0)
                return false;
        }
        return true;
    }
};
