#include<bits/stdc++.h>

using namespace std;

/**
 * Keep track of current continuous length of 0
 * Note begin and end 
 * 
 * Runtime: 12 ms, 89.48%, O(N)
 * Memory Usage: 9.3 MB, 100.00%, O(1)
*/
class Solution1 {
public:
    int maxDistToClosest(vector<int>& seats) {
        int len = seats.size();
        int maxDist = 0, tmpDist = 0;
        
        int i = 0;
        while (seats[i++] != 1) {
            tmpDist++;
        }
        maxDist = max(tmpDist, maxDist);
        
        tmpDist = 0;
        while (i < len) {
            tmpDist++;
            if (seats[i] == 1) {
                maxDist = max(tmpDist/2, maxDist);
                tmpDist = 0;
            }
            
            i++;
        }
        maxDist = max(tmpDist, maxDist);
        
        return maxDist;
    }
};