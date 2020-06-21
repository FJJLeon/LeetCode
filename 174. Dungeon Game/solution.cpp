#include<vector>

using namespace std;

/**
 * dp, from end to start
 * elem of dp array: need[i][j] means the minimum HP need before arrive this point(i,j)
 *                         also means the minimum HP remaining after privous point in a specific path
 * 
 * Runtime: 12 ms, faster than 79.75%, O(M*N)
 * Memory Usage: 9.2 MB, less than 8.31%, O(M*N)
 * 
 * record:
 * 开始写的DP是 from start to end 的，使用了两个矩阵，
 * 一个 need 表示到这个点后所需要的开始点的 HP
 * 一个 remain 表示到这个点后的剩余 HP
 * 在从 left-up 到 bottom-left 的迭代中，更新这两个矩阵，希望 need 更少，而 remain 更多
 * 这就存在问题，到底哪个更重要呢。发现哪个重要都不对，都存在失败的 testcase
 * 比如选择 need 更少的，在DP中，选取了一条路径就丢失了另一条，但是你不知道另一条的 need 虽然多但是 remain 可能也多在后面的路径中会不会更好
 * 1  -3  3        -2  -3   3
 * 0  -2  0        -5  -10  1
 * -3 -3 -3        10   30 -5
 * 上面两个 testcase 分别是选择 need 少 和 reamin 少会导致选择了错误的路径
 * 
 * 然后才想到 from end to start 的 DP
 * 只要到达 end 之后剩余 1 HP 就够了，倒过来走也不存在丢失路径信息的问题，
 * 我只要使得这个点能往下或者往右走就行了，选取所需 HP 少的作为到当前点前所拥有的 HP 即可
*/
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m, n;
        if ((m = dungeon.size()) == 0 || (n = dungeon[0].size()) == 0)
            return -1;
        vector<vector<int>> need(m, vector<int>(n, 0));
        
        need[m-1][n-1] = dungeon[m-1][n-1] > 0 ? 1 : 1 - dungeon[m-1][n-1];        
        for (int j = n-2; j >= 0; --j) {
            int tmp_right = need[m-1][j+1] - dungeon[m-1][j];
            need[m-1][j] = tmp_right > 0 ? tmp_right : 1;
        }
        for (int i = m-2; i >= 0; --i) {
            int tmp_down = need[i+1][n-1] - dungeon[i][n-1];
            need[i][n-1] = tmp_down > 0 ? tmp_down : 1;
            
        }
        for (int i = m-2; i >= 0; --i) {
            for (int j = n-2; j >= 0; --j) {
                int tmp_right = need[i][j+1] - dungeon[i][j],
                    tmp_down = need[i+1][j] - dungeon[i][j];
                
                if (tmp_right <= 0 || tmp_down <= 0) {
                    // go right or down need minimun HP
                    need[i][j] = 1;
                }
                else {
                    // limited HP both needed, use the less one
                    if (tmp_right < tmp_down)
                        need[i][j] = tmp_right;
                    else
                        need[i][j] = tmp_down;
                }
            }
        }

        return need[0][0];
    }
};
