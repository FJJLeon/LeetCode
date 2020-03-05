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
    vector<int> v4(v21.begin()+1, v21.end()-1); // v4 = {2,3,4}, 迭代器初始化，[begin, end) 前闭后开

    /* 
    insert 

    iterator insert( iterator loc, const TYPE &val );                       //在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器
    void insert( iterator loc, size_type num, const TYPE &val );            //在指定位置loc前插入num个值为val的元素
    void insert( iterator loc, input_iterator start, input_iterator end );  //在指定位置loc前插入区间[start, end)的所有元素
    */
    
    /* 
    erase() 删除 (可以用指针来代替迭代器)

    iterator erase( iterator loc );                    //要删除元素的迭代器
    iterator erase( iterator start, iterator end );    //要删除的开头元素的迭代器，要删除的结尾元素的下一个迭代器，前闭后开

    remove() 将等于value的元素放到vector的尾部，但并不减少vector的size

    iterator remove(iterator first, iterator last，val);
    */
    return 0;
}