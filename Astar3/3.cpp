#include<iostream>
#include<limits.h>
#include<algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n, m;
        cin >> n >> m;
        if (n < 2) {
            cout << 0 << endl;
            continue;
        }
            
        long long pair = n / 2;

        if (m < pair) {
            cout << m * (2 * n - 2 * m - 1) << endl;
        }
        else {
            cout << n * (n - 1) / 2 << endl;
        }
        
    }
    return 0;
}