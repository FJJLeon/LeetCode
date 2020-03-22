#include<string>
#include<iostream>

using namespace std;

int main() {
    string s1 = "time", s2 = "me";

    // find
    if (s1.find(s2) != string::npos) {
        cout << s1 << " contains " << s2 << endl;
    }

    // substr(pos, n), s[pos, pos+n]
    string sub1 = s1.substr(1, 2);  // im
    string sub2 = s1.substr(1);     // ime   n   default to s.size() - pos
    string sub3 = s1.substr();      // time  pos default to 0

    return -1;
}