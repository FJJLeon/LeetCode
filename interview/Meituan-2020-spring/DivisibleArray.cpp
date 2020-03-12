#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int maxn = 1e5;
const int mod = 1e9 + 7;
const int maxk = 10;

vector<vector<ll>> dp(maxn, vector<ll>(maxk, 0));

int main() {
    // 由 [l,r] 之间的数组成的长度为 n 的数组，且其和可以被 k 整除，求这样的数组的个数 (取余)
    int n, k, l, r;
    cin >> n >> k >> l >> r;

    for (int h = 0; h < k; h++) {
        dp[1][h] += ((r - h + k) / k - (l - 1 - h + k) / k);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            for (int h = 0; h < k; h++) {
                dp[i + 1][(j + h) % k] += dp[i][j] * ((r - h + k) / k - (l - 1 - h + k) / k);
                dp[i + 1][(j + h) % k] %= mod;
            }
        }
    }
    cout << dp[n][0];
	
}