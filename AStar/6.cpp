#include<iostream>
#include<limits.h>
#include<vector>
#include<algorithm>

using namespace std;

int getValue(int x, int y, vector<double> &l) {
    int cnt;
    int big = max(x, y);
    if (big <= l[0])
        cnt = 4;
    else if (big <= l[1])
        cnt = 3;
    else if (big <= l[2])
        cnt = 2;
    else if (big <= l[3])
        cnt = 1;
    else
        exit(0);

    return (abs(x) + abs(y)) * cnt;
}

int main() {
    int t;
    cin >> t;

    vector<double> l(4);

    vector<int> pointv;
    int k;
    while (t--) {
        cin >> l[0] >> l[1] >> l[2] >> l[3] >> k;
        pointv.push_back(0);
        for (int x = 0; x <= l[3]; ++x) {
            for (int y = 1; y <= l[3]; ++y) {
                int value = getValue(x, y, l);
                pointv.push_back(value);
            }
        }
        sort(pointv.begin(), pointv.end());

        int res = 0, i = 1;
        k--;
        while (k > 0) {
            if (k - 4 >= 0) {
                res += 4 * pointv[i];
                k -= 4;
            }
            else {
                res += k * pointv[i];
                
                k = 0;
            }
            i += 1;
        }
            
        cout << res << endl;

        pointv.clear();
    }

    return 0;
}