/*
母牛从3~7岁初每年会生产1头小母牛，10岁后死亡（10岁仍然存活）
假设初始有一头刚出生的母牛，请问第n年有多少头母牛？（年从第一年开始计数）
n 是虚岁
输入 一个 n 代表第 n 年
输出 第 n 年的牛数量

用一个表记录10种不同年龄的牛，动态变化
AC
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cow(10,0);
    cow[0] = 1;
    for (int i=1; i<n; i++) {
        for (int j=9; j>=1; j--) {
            cow[j] = cow[j-1];
        }
        cow[0] = cow[3-1] + cow[4-1] + cow[5-1] + cow[6-1] + cow[7-1];
    }
    int res = 0;
    for (int i=0; i<10; i++)
        res += cow[i];
    cout << res;
    return 0;
}