#include<map>
#include<iostream>

using namespace std;

int main() {
    /* 初始化 */
    // 访问赋值
    map<string, int> m1;
    m1["red"] = 1;
    // insert
    map<string, int> m2;
    m2.insert({ "red", 1 });
    m2.insert(make_pair("ice", 2));
    m2.insert(pair<string, int>("cream", 3));
    // init with list (c++11)
    map<string,int> m3 = {
        {"red", 1}, {"ice", 2}, {"cream", 3}
    };



    cout << m3["red"];

    return 0;
}