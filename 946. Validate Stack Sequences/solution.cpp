#include<stack>
#include<vector>

using namespace std;

/**
 * Greedy simulate
 * 
 * 使用 stack 模拟 push pop 操作
 * 不断 push，一旦发现栈顶元素等于 popped 当前元素就 pop 直到不等于，直到不能操作
 * 此时若 pop 完则是 合法的 push pop 序列
 * 
 * Runtime: 8 ms, faster than 90.94%
 * Memory Usage: 8.4 MB, less than 100.00%
*/
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int i = 0, j = 0, len = pushed.size();
        while (i<len && j<len) {
            if (i < len) {
                s.push(pushed[i++]);
            }
            // j < len 且 s 非空才能去判断 popped 数组与栈顶是否相等
            while (j < len && !s.empty() && popped[j] == s.top()) {
                s.pop();
                j++;
            }
            if (i == len && j < len) {
                return false;
            }
        }
        
        return true;
    }
};
