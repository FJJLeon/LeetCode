#include<map>
#include<iostream>
#include<assert.h>

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

    /* 删除元素 */
    // 删除指定 key 值
    m3.erase("red");
    assert(m3.find("red") == m3.end());
    
    // 删除迭代器
    auto it = m3.find("ice");
    assert(it != m3.end());
    m3.erase(it);
    assert(m3.find("ice") == m3.end());

    // 删除所有元素
    m3.erase(m3.begin(), m3.end());
    assert(m3.size() == 0);

    m3.insert({"red", 123});
    cout << m3["red"];

    return 0;
}