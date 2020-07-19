#include<iostream>
#include<limits.h>
#include<vector>
#include<algorithm>

using namespace std;

int gcd(int m, int n)
{
    return (n == 0) ? m : gcd(n, m % n);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    std::cin >> t;

    vector<vector<int>> v(1001, vector<int>(1001, 0));
    for (int i = 1; i <= 1000; ++i) {
        for (int j = i; j <= 1000; ++j) {
            if (gcd(i,j) == 1) {
                v[i][j] = max(v[i][j-1], v[i-1][j]) + 1;
            }
            else {
                v[i][j] = max(v[i][j-1], v[i-1][j]);
            }
        }
    }

    while (t--) {
        int a, b;
        cin >> a >> b;
        //scanf("%d %d\n", &a, &b);
        if (a < b)
            cout << v[a][b] << endl;
        else
            cout << v[b][a] << endl;
    }

    return 0;
}