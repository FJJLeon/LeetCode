# 51. N-Queens

## 题目

题面：https://leetcode.com/problems/n-queens/

N 皇后，经典回溯

## 实现

从左往右，在每一列中选择一个安全位置放置皇后，然后继续选择下一列，直到所有列都放置完毕，若能放满每列，则得到一个合法放置，并进行回溯选择其他可能的安全位置。

当然也可以从上往下在每一行中选择一个安全列来做。

### 1. 简单回溯

直接使用棋盘，在枚举时检查棋盘的三个方向来选择安全位置。

``` c++
TC=O(N!)
SC=O(N^2)

class Solution {
public:
    int n;
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        // 初始化棋盘
        vector<string> board(n, string(n, '.'));
        bt(0, board);
        return res;
    }
    
    void bt(int col, vector<string>& board) {
        // 递归终点
        if (col == n) {
            res.push_back(board);
            return;
        }
        // 对于 col 列，遍历每一行选择安全位置
        for (int row = 0; row < n; row++) {
            // 判断 (row, col) 是否安全
            if (isSafe(board, row, col)) {
                // 将皇后放置在 (row, col) 位置
                board[row][col] = 'Q';
                // 继续递归
                bt(col + 1, board);
                // 将皇后移除，回溯
                board[row][col] = '.';
            }
        }
    }
    // 在当前棋盘判断 (row, col) 是否安全
    bool isSafe(vector<string> &board, int row, int col){
        // 横向检查
        for(int j = col; j >= 0; j--)
            if(board[row][j] == 'Q') return false;
        // 斜向上检查
        for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if(board[i][j] == 'Q') return false;
        // 斜向下检查
        for(int i = row, j = col; i < n && j >= 0; i++,j--)
            if(board[i][j] == 'Q') return false;
        
        return true;
    }
};
```

可行的优化方法：
* isSafe 的三个循环可以写成一个
``` c++
    bool isSafe(vector<string> &board, int row, int col) {
        // 循环 step
        for (int s = 0; s <= col; s++) {
            // 横向检查
            if (board[row][s] == 'Q') 
                return false;
            // 斜向上检查，对角线
            if (row - s >= 0 && col - s >= 0 && board[row - s][col - s] == 'Q')
                return false;
            // 斜向下检查，反对角线
            if (row + s < n && col - s >= 0 && board[row + s][col - s] == 'Q') 
                return false;
        }
        return true;
    }
```
* 用三个集合来表示水平线（N条）、对角线（2N-1条）、反对角线（2N-1条）上是否已经有皇后
* 更进一步，集合可以用 bitset 甚至整数掩码来替代降低空间复杂度。但是本题是需要返回 board 的，可以接受。
