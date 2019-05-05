/*
三名特工抓捕恐怖分子
1. 在字节跳动大街的N个建筑中选定3个埋伏地点
2. 为了相互照应，我们决定相距最远的两名特工间的距离不超过D
给定N（可选作为埋伏点的建筑物数）、D（距离最远的两名特工的最大值）以及可选建筑物的坐标，计算在这次行动中，共有多少种埋伏选择。
注意：1.两个特工不能埋伏在同一地点 2.三个特工是等价的：即同样的位置组合（A、B、C）只算一种方案，特工之间互换位置不算
输入描述：
第一行包含空格分隔的两个数字N和D（1<=N<=1000000, 1<=D<=N）。
第二行包含N个建筑物的位置，每个位置用一个整数表示，从小到大排列（将字节跳动大街看做一个数组）
输出描述：
一个数字，表示不同埋伏方案的数量。结果可能溢出，请对 99997867 取模

20 分？为啥 TODO
*/

#include <bits/stdc++.h>
using namespace std;

int Cn3(int n) {
    if (n<3)
        return 0;
    else
        return n * (n-1) * (n-2) / 6;
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> place(n);
    for (int i=0; i<n; i++)
        cin >> place[i];
    int res = 0;
    sort(place.begin(), place.end());
    int i = 0;
    while (i<n) {
        int a = place[i];
        int k = i; 
        while (k+1<n && place[k+1] - a <= d) {
            k++;
        }
        int count = k - i + 1;
        int tmp = Cn3(count);
        res = (res + tmp) % 99997867;

        i = k-1 > i ? k-1 : i+1;
    }
    
    cout << res;
    return 0;
}