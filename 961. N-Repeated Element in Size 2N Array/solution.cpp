#include<vector>
#include<unordered_set>

using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_set<int> exist;
        for (int i : A) {
            if (exist.count(i))
                return i;
            exist.insert(i);
        }
        // won't reach
        return 0;
    }
};