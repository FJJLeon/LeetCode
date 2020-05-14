#include<string>
#include<stack>

using namespace std;

/**
 * greedy
 * how to get a smallest new number by removing only one digit?
 *  we need to remove a digit who is the first one (left to right) whose next digit is smaller than it, aka first peak
 *  for "1293847", it is 9, its next is 3 < 9 and previous digits are smaller too
 *  for  "123847"-> 8
 *        "12347"-> 7
 *             ...
 * 
 * Runtime: 8 ms, faster than 62.37%, O(N)
 * Memory Usage: 10.7 MB, less than 9.09%, O(N)
*/
class Solution {
public:
    string removeKdigits(string num, int k) {
        int len = num.size();
        if (len == k)
            return "0";
        // maintain previous incresing digit sequence
        stack<char> is;
        int i = 0;
        // traverse all digits
        while (i < len) {
            // maintain new incresing digit sequence
            if (is.empty() || is.top() <= num[i]) {
                is.push(num[i++]);
            }
            // find a peak(is.top) should be removed
            else {
                if (k > 0) {
                    is.pop();
                    if (--k == 0)
                        break;
                }
            }
        }
        // for testcase like "123456789", all digits pushed into stack, but no remove perfomed, now perform
        while (k != 0) {
            is.pop();
            --k;
        }
        // construct result = is.bottom ... is.top + leftover num
        string res = num.substr(i);
        while (!is.empty()) {
            res = is.top() + res;
            is.pop();
        }
        // remove leading zero
        int notzero = 0;
        while (res[notzero] == '0')
            ++notzero;
        res = res.substr(notzero);
        // return res if not ""
        return  res == "" ? "0" : res;
    }
};
