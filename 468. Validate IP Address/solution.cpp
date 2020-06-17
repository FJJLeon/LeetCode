#include<string>
#include<vector>

using namespace std;


/**
 * first solution
 * check IPv4 or IPv6
 * split input string
 * check each string format
 * 
 * Runtime: 0 ms
 * Memory Usage: 6.4 MB
*/
class Solution1 {
private:
    size_t dot, colon;
    vector<string> splited;

    vector<string> split(string in, char delimiter) {
        vector<string> res;
        size_t left = 0, right = 0;
        while ((right = in.find(delimiter, left)) != string::npos) {
            res.push_back(in.substr(left, right - left));
            left = right + 1;
        }
        res.push_back(in.substr(left));
        return res;
    }
    bool isIPv4(vector<string> splited) {
        if (splited.size() != 4)
            return false;
        for (string &s : splited) {
            if (!isIPv4Token(s))
                return false;
        }
        return true;
    }
    bool isIPv4Token(string s) {
        if (s.size() > 3 || s.size() < 1)
            return false;
        if (s.size() > 1 && s[0] == '0')
            return false;
        for (char &c : s) {
            if (c < '0' || c > '9')
                return false;
        }
        if (stoi(s) > 255)
            return false;
    }

    bool isIPv6(vector<string> splited) {
        if (splited.size() != 8)
            return false;
        for (string &s : splited) {
            if (!isIPv6Token(s))
                return false;
        }
        return true;
    }
    bool isIPv6Token(string s) {
        if (s.size() > 4 || s.size() < 1)
            return false;
        for (char &c : s) {
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                return false;
        }
    }
public:
    string validIPAddress(string IP) {
        dot   = IP.find('.');
        colon = IP.find(':');
        string res = "Neither";
        if (dot != string::npos && colon != string::npos) {

        }
        else if (dot != string::npos) {
            splited = split(IP, '.');
            if (isIPv4(splited)) {
                res = "IPv4";
            }
        }
        else if (colon != string::npos) {
            splited = split(IP, ':');
            if (isIPv6(splited)) {
                res = "IPv6";
            }
        }
        
        return res;
    }
};

