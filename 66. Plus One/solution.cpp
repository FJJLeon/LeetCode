#include<vector>

using namespace std;

/**
 * reverse iterator
 * 
 * Runtime: 4 ms, faster than 57.17%, O(N)
 * Memory Usage: 8.7 MB, less than 90.17%, O(1)
*/
class Solution1 {
public:
    vector<int> plusOne(vector<int>& digits) {
        auto rit = digits.rbegin();
        // plus one
        int carry = 1;
        // traverse from back to front
        while (rit != digits.rend()) {
            // require carry
            if (*rit == 9) {
                *rit = 0;
            }
            // no carry, break
            else {
                *rit += carry;
                carry = 0;
                break;
            }
            ++rit;
        }
        // traverse all and still carry, like [9,9,9] -> [1,0,0,0]
        if (rit == digits.rend() && carry == 1) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};


/**
 * long long ago code, bad
 * / and % operation consume more time
 * 
 * Runtime: 8 ms, faster than 6.65%
 * Memory Usage: 8.9 MB, less than 29.47%
*/
class Solution2 {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size();
        int carry = 1, i = len, tmp;
        
        while (i > 0) {
            tmp = digits[i - 1] + carry;
            carry = tmp / 10;
            digits[i - 1] = tmp % 10;
            if (carry == 0)
                return digits;
            i--;
        }
        
        if (carry == 1){
            digits.insert(digits.begin(), 1);
            return digits;
        }
        
        return digits;
    }
};