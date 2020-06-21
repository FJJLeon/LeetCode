#include<vector>

using namespace std;

/**
 * dp, from end to start
 * elem of dp array: need[i][j] means the minimum HP need before arrive this point(i,j)
 *                         also means the minimum HP remaining after privous point in a specific path
 * 
 * Runtime: 12 ms, faster than 79.75%, O(M*N)
 * Memory Usage: 9.2 MB, less than 8.31%, O(M*N)
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
