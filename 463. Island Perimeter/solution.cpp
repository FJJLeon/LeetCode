#include<vector>
#include<iostream>

using namespace std;

/**
 * stright count one side by one side
 * 
 * Runtime: 76 ms, faster than 45.38%, O(5*M*N)
 * Memory Usage: 14.1 MB, less than 100.00%
*/
class Solution1 {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int perimeter = 0; 
        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {
                if (grid[i][j] == 1) {
                    if (i==0 || grid[i-1][j] == 0)  // up 
                        ++perimeter;
                    if (j==0 || grid[i][j-1] == 0)  // left
                        ++perimeter;
                    if (i==m-1 || grid[i+1][j] == 0)// down
                        ++perimeter;
                    if (j==n-1 || grid[i][j+1] == 0)// right
                        ++perimeter;
                }
            }
        }
        
        return perimeter;
    }
};

/**
 * math 
 * when two island is neighbor, 2 sides disappear
 *    口  +  口  ->  日， 4 + 4 -> 6
 * 
 * Runtime: 68 ms, faster than 75.98%, O(3*M*N)
 * Memory Usage: 13.9 MB, less than 100.00%
*/
class Solution2 {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        int island = 0, repeat = 0; 
        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {
                if (grid[i][j] == 1) {
                    // count island number
                    island++;
                    
                    if (i != m-1 && grid[i+1][j] == 1) // count right neighbor
                        repeat++;
                    if (j != n-1 && grid[i][j+1] == 1) // count down neighbor
                        repeat++;
                }
            }
        }
        
        return island*4 - repeat*2;
    }
};