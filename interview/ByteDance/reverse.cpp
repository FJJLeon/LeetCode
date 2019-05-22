#include <iostream>
#include <string>
using namespace std;

void reverse_base(char str[], int begin, int end) {
    char tmp;
    int size = end - begin;
    for (int i=begin; i<begin + size/2; i++) {
        tmp = str[i];
        str[i] = str[size-i-1];
        str[size-i-1] = tmp;
    }
}

void reverse(char str[]) {
    int size = sizeof(str);
    reverse_base(str, 0, size);
    int form = 0;
    for (int i=0; i<size; i++) {
        if (str[i] == ' ') {
            reverse_base(str, form, i);
            form = i;
        }
    }
    reverse_base(str, form, size);
}

int main() {
    string s;
    cin >> s;
    int len = s.length();
    int last = len;
    for (int i=len-1; i>=0; i--) {
        if (s[i] == ' ') {
            cout << s.substr(i, last-i) << ' ';
            last = i;
        }
    }
    cout << s.substr(0, last);
    return 0;
}

//
// SQL: group by having ?

// 最长不重复子串
// sliding window + char map
int main() {
    string s;
    cin >> s;
}