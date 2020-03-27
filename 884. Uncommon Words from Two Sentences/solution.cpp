#include<vector>
#include<string>
#include<unordered_map>
#include<sstream>

using namespace std;

/**
 * note the uncommon word only appear once whereever(A and B)
 * use istringstream split 
 * 
 * Runtime: 0 ms, faster than 100.00%, O(M+N), len(A)=M, len(B)=N
 * Memory Usage: 6.9 MB, less than 100.00%, O(M+N)
*/
class Solution {
public:
    vector<string> uncommonFromSentences(string A, string B) {
        // map record count of each word
        unordered_map<string, int> count;
        // use istringstream split string
        istringstream iss(A + ' ' + B);
        string s;
        while (iss >> s)
            ++count[s];
        
        vector<string> res;
        for (auto c : count)
            if (c.second == 1)
                // uncommon word
                res.push_back(c.first);
        return res;
    }
};