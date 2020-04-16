#include<string>
#include<vector>
#include<stack>

using namespace std;

/**
 * My Solution, greedy
 * intuition: based on simple parenthesis string consist of ( and ) only
 *  1. traverse from left to right, use two variable record left bracket and asterisk
 *     ( : countLeft + 1
 *     * : countStar + 1
 *     ) : use left bracket first if remains left, or use asterisk, or the string is invalid
 *  2. at last, if countStar is bigger than countLeft, asterisk is enough to pair
 *  3. however, it CANNOT be guaranteed that remaining asterisks appear on the right of left bracket
 *  4. traverse from right to left, using right bracket actively pair could sovle this flaw
 * 
 * Runtime: 0 ms, faster than 100.00%, O(N) but two-pass
 * Memory Usage: 6.2 MB, less than 100.00%, O(1)
*/
class Solution11 {
public:
    bool checkValidString(string s) {
        if (s.empty())
            return true;
        int len = s.size();
        int countStar = 0, countLeft = 0;
        for (int i = 0; i < len; ++i) {
            switch (s[i]) {
                case '(':
                    ++countLeft;
                    break;
                case '*':
                    ++countStar;
                    break;
                case ')':
                    if (countLeft > 0)
                        --countLeft;
                    else if (countStar > 0)
                        --countStar;
                    else
                        return false;
                    break;
            }
        }
        
        countStar = 0;
        int countRight = 0;
        for (int i = len - 1; i >= 0; --i) {
            switch (s[i]) {
                case ')':
                    ++countRight;
                    break;
                case '*':
                    ++countStar;
                    break;
                case '(':
                    if (countRight > 0)
                        --countRight;
                    else if (countStar > 0)
                        --countStar;
                    else
                        return false;
                    break;
            }
        }
        
        return true;
    }
};

/**
 * trade space for time based 11
 * record index of left bracket and asterisk when traverse from left to right
 * now after finishing traversing, we can judge whether asterisk appear on thr right of left bracket
 * 
 * Runtime: 0 ms, faster than 100.00%, O(N) one-pass, worst two-pass
 * Memory Usage: 6.3 MB, less than 100.00%, O(N)
*/
class Solution12 {
public:
    bool checkValidString(string s) {
        if (s.empty())
            return true;
        int len = s.size();
        stack<int> left, star;
        for (int i = 0; i < len; ++i) {
            switch (s[i]) {
                case '(':
                    left.push(i);
                    break;
                case '*':
                    star.push(i);
                    break;
                case ')':
                    if (!left.empty())
                        left.pop();
                    else if (!star.empty())
                        star.pop();
                    else
                        return false;
            }
        }
        while (!left.empty() && !star.empty()) {
            if (left.top() > star.top())
                return false;
            left.pop();
            star.pop();
        }
        
        return left.empty();
    }
};

/**
 * record the number range of valid open parenthesis, 
 * ex: 
 *  **(    [1, 3] number of '(' to be paired can be 1, 2, 3.          1 for '**(', 3 for '((('
 *  (**(*  [0, 5] number of '(' to be paired can be 0, 1, 2, 3, 4, 5. 0 for '()*()', 4 for '((((('
 * record lower and upper bound of range is enough
 * encounter:
 *  ( , [lo, hi] -> [lo+1, hi+1]
 *  * , [lo, hi] -> [lo-1, hi+1]
 *  ) , [lo, hi] -> [lo-1, hi-1]
 * in addition:
 *  lo < 0 is no use, a valid string ended with exist lo == 0
 *  hi cannot be negative
 * 
 * Runtime: 0 ms, faster than 100.00%, O(N), one-pass
 * Memory Usage: 6 MB, less than 100.00%, O(1)
*/
class Solution13 {
public:
    bool checkValidString(string s) {
        int lo = 0, hi = 0;
        for (char c : s) {
            switch (c) {
                case '(':
                    ++lo;
                    ++hi;
                    break;
                case '*':
                    // use * as )
                    --lo;
                    // use * as (
                    ++hi;
                    break;
                case ')':
                    --lo;
                    --hi;
                    break;
            }
            lo = max(lo, 0);
            if (hi < 0)
                return false;
        }
        
        return lo == 0;
    }
    // simplify code, agg * to ()
    bool checkValidStringAgg(string s) {
       int lo = 0, hi = 0;
       for (char c: s) {
           // only c == '(', lo++, or lo--
           lo += c == '(' ? 1 : -1;
           // only c != ')', hi++, or hi--
           hi += c != ')' ? 1 : -1;
           lo = max(lo, 0);
           if (hi < 0) break;
       }
       return lo == 0;
    }
};


/**
 * Recursive
 * try all possible situation for each asterisk, degenerate to onlu '()' involved
 * 
 * Time Limit Exceeded, O(3^N)
 * for JAVA
 *      Runtime: 377 ms
*/
class Solution21 {
public:
    bool checkValidString(string s) {
        return checkBasic(s, 0, 0);
    }
private:
    bool checkBasic(string s, int pos, int count) {
        // recursive export
        if (pos == s.size())
            return count == 0;
        // early return, count < 0 must be invalid
        if (count < 0)
            return false;
        
        bool res;
        switch (s[pos]) {
            case '(':
                res = checkBasic(s, pos + 1, count + 1);
                break;
            case ')':
                res = checkBasic(s, pos + 1, count - 1);
                break;
            case '*':
                res = checkBasic(s, pos + 1, count + 1)    // as '('
                    || checkBasic(s, pos + 1, count    )    // as ' '
                    || checkBasic(s, pos + 1, count - 1);   // as ')'
                break;
        }
        
        return res;
    }
};

/**
 * use dp memo encountered state for a position and count 
 * dp[pos][count]: recursive traverse to the position, previous asterisk choice lead to the count, is this possible valid for following choice
 * ex:
 *      ***()  dp[2][0] is calculated in dp[0][0], there are several path leading to dp[2][0], we can reuse it
 * 
 * Time Limit Exceeded, O(N^2)
 * for JAVA
 *      Runtime: 1 ms
*/
class Solution22 {
public:
    bool checkValidString(string s) {
        dp = vector<vector<int>>(s.size(), vector<int>(s.size(), 0));
        return checkBasic(s, 0, 0);
    }
private:
    vector<vector<int>> dp;
    bool checkBasic(string s, int pos, int count) {
        // recursive export
        if (pos == s.size())
            return count == 0;
        // early return, count < 0 must be invalid
        if (count < 0)
            return false;
        // stated already encountered
        if (dp[pos][count] != 0)
            return dp[pos][count];
        
        bool res;
        switch (s[pos]) {
            case '(':
                res = checkBasic(s, pos + 1, count + 1);
                break;
            case ')':
                res = checkBasic(s, pos + 1, count - 1);
                break;
            case '*':
                res = checkBasic(s, pos + 1, count + 1)    // as '('
                    || checkBasic(s, pos + 1, count    )    // as ' '
                    || checkBasic(s, pos + 1, count - 1);   // as ')'
                break;
        }
        dp[pos][count] = res;
        return res;
    }
};
