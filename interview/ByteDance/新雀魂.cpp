/*
自定义了雀魂麻将的规则：
1. 共有36张牌，每张牌是1~9，每个数字4张牌。
2. 你手里有其中的14张牌，如果这14张牌满足如下条件，即算作和牌：
    14张牌中有2张相同数字的牌，称为雀头。
    除去上述2张牌，剩下12张牌可以组成4个顺子或刻子。
        顺子为递增的连续3个数字牌（如234,567）
        刻子为3个相同的数字牌（如：111,777）
现在，小包从36张牌中抽取了13张牌，他想知道在剩下的23张中取一张牌，取到哪几种数字可以和牌。
输入描述：输入只有一行，包含13个数组，用空格分隔，每个数字在1~9之间，保证同种数字最多出现4次。
输出描述：输出同样是一行，包含1个或以上的数字。代表他再次取到哪种数字可以和牌。若满足条件的有多种，请按从小到大的顺序输出。若无法和牌，请输出一个数字0。

仅过 20%，必然是雀头 + 4个刻子
使用递归判断，在可以的情况下用前面的排作为 雀头、刻子、顺子，然后去除判断接下来的排，代码见 quehun.py
*/
#include <bits/stdc++.h>
using namespace std;

const int nums = 14; 
    
bool judge(vector<int> v) {
    assert(v.size() == nums);
    vector<int> count(nums, 0);
    sort(v.begin(), v.end());
    for (int i=0; i<nums; i++) {
        count[v[i] - 1] += 1;
    }
    bool flag = false;
    int count3 = 0, count2 = 0;
    for (int i=0; i<nums; i++) {
        if (count[i] == 3)
            count3 += 1;
        if (count[i] == 2)
            count2 += 1;
    }
    if (count3 == 4 && count2 == 1)
        flag = true;
    return flag;
}

int main() {
    vector<int> card(nums-1,0);
    for (int i=0; i<nums-1; i++){
        cin >> card[i];
    }
    for (int i=1; i<=nums; i++) {
        card.push_back(i);
        if (judge(card)) 
            cout << i << " ";
        card.pop_back();
    }
    return 0;
}