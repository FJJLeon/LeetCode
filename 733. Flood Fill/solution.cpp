#include<vector>

using namespace std;

/**
 * recursive dfs flood fill
 * 
 * Runtime: 16 ms, O(N)
 * Memory Usage: 14.1 MB, O(N)
*/
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int row = image.size(), col = image[0].size();
        int originColor = image[sr][sc];
        if (originColor == newColor)
            return image;
        
        vector<vector<int>> backup(image);
        recurFlood(backup, sr, sc, originColor, newColor);
        
        return backup;
    }
private:
    
    void recurFlood(vector<vector<int>>& image, int r, int c, int originColor, int newColor) {
        image[r][c] = newColor;
        int row = image.size(), col = image[0].size();
        if (r-1 >= 0 && image[r-1][c] == originColor)
            recurFlood(image, r-1, c, originColor, newColor);
        if (r+1 < row && image[r+1][c] == originColor)
            recurFlood(image, r+1, c, originColor, newColor);
        if (c-1 >= 0 && image[r][c-1] == originColor)
            recurFlood(image, r, c-1, originColor, newColor);
        if (c+1 < col && image[r][c+1] == originColor)
            recurFlood(image, r, c+1, originColor, newColor);
    }
};
