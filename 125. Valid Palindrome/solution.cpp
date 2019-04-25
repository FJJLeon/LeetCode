#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        if (s == "")
            return true;
        
        string::iterator i = s.begin();
        string::reverse_iterator  j = s.rbegin();
        while (i+1 < j.base()) {
            // cannot change compare order, shortcut
            while (i != s.end() && !isValid(*i))
                i++;
            while (j != s.rend() && !isValid(*j))
                j++;
            if (i > j.base())
                break;
            if (toLower(*i) != toLower(*j))
                return false;
            i++; j++;
        }
        /*
        int i = 0, j = s.length()-1;
        while (i < j) {
            while (!isValid(s[i]) && i != s.length()-1)
                i++;
            while (!isValid(s[j]) && j != 0)
                j--;
            if (i > j)
                break;
            if (toLower(s[i]) != toLower(s[j]))
                return false;
            i++; j--;
        }
        */
        return true;
    }
private:
    bool isValid(char c) {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
            return true;
        else 
            return false;
    }
    char toLower(char c) {
        if (c >= 65 && c <= 90)
            return c + 32;
        else
            return c;
    }
};

string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

int main() {
    string line;
    while (getline(cin, line)) {
        string s = stringToString(line);
        
        bool ret = Solution().isPalindrome(s);

        string out = boolToString(ret);
        cout << out << endl;
    }
    return 0;
}