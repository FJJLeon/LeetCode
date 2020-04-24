#include<string>
#include<assert.h>

using namespace std;

/**
 * Euclidean algorithm
 *      gcd(a,b)=gcd(b, a mod b)
 * but not completely the same, integer must have a smallest gcd = '1' while string not
 * firstly we should make sure that the longer one begin with the shorter one
 * 
 * Runtime: 4 ms, faster than 93.45%, O(N^2), N = max(Len1, Len2)
 * Memory Usage: 7.4 MB, less than 100.00%, O(N^2), N = max(Len1, Len2)
*/
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int len1 = str1.size(), len2 = str2.size();
        if (len1 < len2)
            return gcdOfStrings(str2, str1);
        // make sure that the longer one begin with the shorter one
        if (str1.find(str2) == 0)
            return str2 == "" ? str1 : gcdOfStrings(str2, modString(str1, str2));
        else
            return "";
    }
private:
    string modString(string s1, string s2) {
        int len2 = s2.size();
        while (s1.find(s2) == 0)
            s1 = s1.substr(len2);
        return s1;
    }
};