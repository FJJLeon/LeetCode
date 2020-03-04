#include<vector>
#include<iostream>

using namespace std;

int main() {
    /* init */
    vector<int> v0;                     // size:0, capacity:0
    vector<int> v11(5);                 // size:5, 初始化为默认值，此处为 0
    vector<int> v12(5, 6);              // size:5, 初始化为 6
    vector<int> v21 = {1, 2, 3, 4, 5};  // 用 list 初始化
    vector<int> v22{1, 2, 3, 4, 5};
    vector<int> v31 = v21;              // 用 vector 初始化，拷贝
    vector<int> v32(v11);
    vector<int> v4(v21.begin()+1, v21.end()-1); // v4 = {2,3,4}, 迭代器初始化，前闭后开

    return 0;
}