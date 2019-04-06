#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
using namespace std;

// give the minimum number of coins for change [1..m]
// giving n kind of coins
// only 10% score, why?? gg
/*
 sample:
 input:
    20 4
    1
    2
    5
    10
 output:
    5
*/
const long MAXNUM = pow(2,31)-1; 

int main() {
    // give [1,m] with n kind coin
    long m, n;
    //scanf("%lld %lld", m);
    cin >> m >> n;
    //cin >> n;
    //cin >> m >> n;
    vector<long> coin(n);
    for (long i=0; i<n; i++)
        cin >> coin[i];
    vector<long> givem(m+1, 0);
    vector< vector<long> > cospCoin(m+1, vector<long>(n,0));
    for (long i=1; i<m; i++) {
        
        long whichCoin = -1;
        
        for (long c=0; c<n; c++) {
            if (coin[c] == i) {
                whichCoin = c;
                break;
            }
        }
        if (whichCoin != -1) {
            givem[i] = 1;
            cospCoin[i][whichCoin] = 1;
            continue;
        }
        
        long curMin = MAXNUM;
        
        for (long c=0; c<n; c++) {
            // if coin[c] enough for m and dp is less
            if (i > coin[c] && givem[i - coin[c]] < curMin) {
                curMin = givem[i - coin[c]];
                whichCoin = c;
            }
        }
        givem[i] = curMin + 1;
        cospCoin[i] = cospCoin[i-coin[whichCoin]];
        cospCoin[i][whichCoin] += 1;
    }
    /*
    for (long i=1; i<m; i++) {
        cout << "for m = " << i << ", need " << givem[i] << " coins. each as follow:" << endl;
        for (long c=0; c<n; c++)
            cout << cospCoin[i][c] << " ";
        cout << endl;
    }*/
    vector<long> res(n,0);
    for (long i=1; i<m; i++) {
        for (long c=0; c<n; c++) {
            if (cospCoin[i][c] > res[c])
                res[c] = cospCoin[i][c];
        }
    }
    long need = 0;
    for (long c=0; c<n; c++)
        need += res[c];
    cout << need;

    return 0;
}