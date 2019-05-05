/*
给定一个长度为n的，仅包含0,1的数组。例如1,0,0,1,1,1,0。我们可以轻易算出，它的最长全1区间长度是3。从数组的第4位到第6位。
现在，你获得了k次可以将某个位置上的0变为1的机会，但可以不用完所有的机会。
请你给出，你使用了你的变化机会后，这个数列的最长全1区间最大是多少

输入 n k 接着一行 n 个数
sliding window
AC
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i=0; i<n; i++)
        cin >> v[i];
    int i=0, j=0;
    int maxlen = 0;
    int curWin = 0;
    int curOp = 0;
    queue<int> q;
    while (j < n) {
        if (v[j] == 0) {
            // if still can direct change
            if (curOp < k) {
                q.push(j);
                v[j] = 1;
                curOp++;
            }
            // cannot direct change, but can cancel first
            else if (!q.empty()) {
                // cancel first, and set i to first + 1
                int tmp = q.front();
                v[tmp] = 0;
                i = tmp + 1;
                q.pop();
                q.push(j);
                v[j] = 1;
            }
            // cannot change, k = 0
            else {
                i = j + 1;
            }
        }
        // can direct add to window
        else {
            
        }
        curWin = j-i+1;
        maxlen = curWin > maxlen ? curWin : maxlen;
        
        j++;
    }
    
    cout << maxlen;
    return 0;
}