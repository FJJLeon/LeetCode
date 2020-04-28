#include<queue>
#include<list>
#include<assert.h>

int main() {
    /* 初始化 */
    std::deque<int> underDeque(3, 1);
    std::list<int> underList(3, 2);

    std::queue<int> one;
    std::queue<int, std::list<int>> two; // 使用 list 作为底层容器初始化

    std::queue<int> three(one); // 拷贝 queue 初始化
    std::queue<int> four(underDeque); // 拷贝 deque 初始化
    std::queue<int, std::list<int>> five(underList); // 拷贝 list 初始化
    
    assert(!four.empty());
    assert(four.front() == 1);
    assert(five.front() == 2);
    
    /**
     * 清空
     * queue 不提供 clear 方法
    */
    std::queue<int> empty1;
    std::queue<int, std::list<int>> empty2;

    three = empty1; // 用空对象赋值

    while (!four.empty()) // 循环 pop
        four.pop();
    
    std::swap(five, empty2); // swap ，据说最高效，but why

    assert(four.empty());
    assert(five.empty());

    return 0;
}