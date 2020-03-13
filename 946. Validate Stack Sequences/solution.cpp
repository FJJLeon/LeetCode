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
 * Runtime: 8 ms, 90.94%, O(N)
 * Memory Usage: 8.4 MB, 100.00%, O(N)
*/
class Solution1 {
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

/** 
 * 优化成 O(1) 空间复杂度，复用 pushed 数组
 * 然而 pushed 是 &，这样修改了输入
 * 
 * Runtime: 8 ms, 90.94%
 * Memory Usage: 7.9 MB, 100.00%
*/
class Solution2 {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        // s for length of stack(pushed)
        int i = 0, j = 0, s = 0, len = pushed.size();
        while (i < len && j < len) {
            if (i < len) {
                pushed[s++] = pushed[i++];
            }
            // j < len 且 s 非空才能去判断 popped 数组与栈顶(pushed[s-1])是否相等
            while (j < len && s > 0 && popped[j] == pushed[s-1]) {
                s--;
                j++;
            }
            if (i == len && j < len) {
                return false;
            }
        }
        
        return true;
    }
};