#include<set>
#include<iostream>
#include<vector>

using namespace std;

int main() {
/* 初始化 */
    // 插入
    set<int> s1;    // 默认初始化 小于比较器 less<int>
    s1.insert(1);
    // 数组构造
    int a[5] = {1, 2, 2, 4, 5};
    set<int> s2(a, a+5);  // size = 4
    // 迭代器区间构造
    vector<int> v = {1, 2, 2, 4, 5};
    set<int> s3(v.begin(), v.end());
    // 拷贝构造
    set<int> s4(s2);

/* 判断元素存在 */
    if (s2.find(3) == s2.end())
        cout << "3 not exist in s2" << endl; 
/* 删除 */ 
    s2.erase(1);    // 按元素值删除
    s2.erase(s2.begin());   // 删除迭代器指向元素
    s3.erase(s3.begin()++, s3.end());   // 删除区间[s, e)
    
    return 0;
}