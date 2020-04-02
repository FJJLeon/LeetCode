#include<set>

using namespace std;

/**
 * Runtime: 4 ms
 * Memory Usage: 6.4 MB
*/
class Solution {
public:
    bool isHappy(int n) {
        set<int> exist;
        
        while (n != 1) {
            exist.insert(n);
            n = process(n);
            if (exist.find(n) != exist.end()) {
                return false;
            }
        }
        
        return true;  
    }
private:
    int process(int n) {
        int res = 0;
        while (n > 0) {
            res += (n % 10) * (n % 10);
            n /= 10;
        }
        return res;
    }
};