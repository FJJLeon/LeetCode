#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> data;
    int k;
    
    int tmp;
    string s;
    getline(cin, s);
    /*
    scanf("[%d,", tmp);
    data.push_back(tmp);
    int i = 1;
    while (scanf("%d,", tmp)) {
        data.push_back(tmp);
        i++;
    }
    scanf("%d]", tmp);
    data.push_back(tmp);
    */
    cout << s;
    return 0;
}

int datalen = data.size();
    vector<string> stack;
    vector<string> res;
    for (int i=0; i<datalen; i++) {
        if ((i+1) % k == 0) {
            for (int j=k-1; j>=0; j--) {
                res.push_back(stack[j]);
            }
            stack.clear();
        }
        stack.push_back(data[i]);
    }



// 2
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> data;
    int k;
    
    string s;
    getline(cin, s);
    cin >> k;
    // input
    int cur = 1;
    int slen = s.length();
    string tmp;
    for (int i=1; i<slen; i++) {
        if (s[i] == ',') {
            tmp = s.substr(cur, i-cur);
            cur = i + 1;
            data.push_back(tmp);
        }
    }
    tmp = s.substr(cur, slen-cur-1);
    data.push_back(tmp);
    
    int datalen = data.size();
    int count = datalen / k;
    for (int i=0; i<count; i++) {
        reverse(data.begin()+i*k, data.begin()+(i+1)*k);
    }   
    
    cout << "[";
    for (int i=0; i<data.size()-1; i++) {
        cout << data[i] << ",";
    }
    cout << *(data.end()-1) << "]";
    return 0;
}

// 1
#include <bits/stdc++.h>

using namespace std;

int main() {
    set<char> data;
    char tmp;
    bool flag = true;
    while (cin.get(tmp)) {
        if (tmp == ',')
            continue;
        if (data.find(tmp) != data.end()) {
            flag = false;
            break;
        }
        data.insert(tmp);
    }
    if (flag)
        cout << "false";
    else
        cout << "true";
    return 0;
}

// 3
#include <bits/stdc++.h>

using namespace std;

int countXie(string s) {
    int len = s.length();
    int res = 0;
    for (int i=0; i<len-1; i++) {
        if (s[i] == '/')
            res++;
    }
    return res;
}

int countString(vector<string> v, string target) {
    int vlen = v.size();
    int res = 0;
    for (int i=0; i<vlen; i++) {
        if (v[i] == target) {
            res++;
        }
    }
    return res;
}

int main() {
    int k;
    vector<string> data;
    cin >> k;
    string tmp;
    vector<int> res;
    for (int i=0; i<k; i++) {
        cin >> tmp;
        int tmplen = tmp.length();
        if (tmp[tmplen-1] == '/')
            tmp = tmp.substr(0, tmplen-1);
        
        if (i==0) {
            int countX = countXie(tmp);
            for (int j=0; j<countX; j++) cout << 1;
            cout << ' ';
        }
        else {
            int countS = countString(data, tmp);
            int countX = countXie(tmp);
            for (int j=0; j<countX; j++) {
                if (j==0 || j==countX-1)
                    cout << 1;
                else 
                    cout << countS+1; 
            }
            cout << ' ';
        }
        data.push_back(tmp);
    }
    
    return 0;
}