#include<iostream>
#include<limits.h>
#include<algorithm>
#include<vector>

using namespace std;

bool compare(const pair<int,char> a, const pair<int ,char> b) {
    return a.second < b.second;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> c(n);
        
        int x, y;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            c[i] = make_pair(x, y);
        }
        sort(c.begin(), c.end(), compare);
        
        

    }
    return 0;
}