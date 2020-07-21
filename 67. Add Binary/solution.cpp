#include<string>
#include<iostream>

using namespace std;

/**
 * 
*/
class Solution1 {
public:
    string addBinary(string a, string b) {
        // make sure 'a' shorter
        if (a.length() > b.length())
            return addBinary(b, a);
        
        auto ait = a.rbegin(), bit = b.rbegin();
        string res = "";
        int carry = 0;
        while (ait != a.rend() || bit != b.rend()) {
            if (ait == a.rend()) {
                if (carry == 0) {
                    int dis = distance(b.rbegin(), bit);
                    res = b.substr(0, b.length() - dis) + res;
                    break;
                }
                else {
                    if (*bit == '0') {
                        res = '1' + res;
                        carry = 0;
                    }
                    else {
                        res = '0' + res;
                    }
                    bit++;
                }
            }
            else {
                int x = *ait == '0' ? 0 : 1,
                    y = *bit == '0' ? 0 : 1;
                res = ((x + y + carry) % 2 == 1 ? '1' : '0') + res;
                carry = (x + y + carry) >= 2 ? 1 : 0;
                ait++; bit++;
            }
        }
        
        if (carry == 1)
            res = '1' + res;
        
        return res;
    }
};

int main () {
    string a = "100", b = "110010";
    cout << Solution1().addBinary(b, a);

    return 0;
}