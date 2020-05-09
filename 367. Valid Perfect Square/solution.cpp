

/**
 * linear naive search
 * 
 * Runtime: O(N)
*/
class Solution11 {
public:
    bool isPerfectSquare(int num) {
        for (long i = 0; i*i <= num; ++i) {
            if (i * i == num)
                return true;
        }
        return false;
    }
};

/**
 * binary search
 * 
 * Runtime: O(log(N))
*/
class Solution12 {
public:
    bool isPerfectSquare(int num) {
        long lo = 0, hi = num, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (mid * mid == num)
                return true;
            else if (mid * mid < num)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return false;
    }
};

/**
 * x = 1 + 3 + 5 + 7 +... if x is perfect square number
 *  等差数列求和
 *  an = 2n-1, Sn = n^2
 * 
 * Runtime: O(sqrt(N))
*/
class Solution2 {
public:
    bool isPerfectSquare(int num) {
        int odd = 1;
        while (num > 0) {
            num -= odd;
            odd += 2;
        }
        return 0 == num;
    }
};

/**
 * Newton's Method solve approximate root
 * x(n+1) = x(n)－f(x(n))/f'(x(n))
 * for f(x) = x^2, f'(x) = 2*x
 * 
 * for equation x^2 - num = 0
 * a more approximate root for x0 is 
 *  x1 = x0 - f(x0) / f'(x0) = x0 - (x0^2 - num) / (2 * x0) = (x0 + num / x0) / 2
 * 
 * Runtime: ?
*/
class Solution3 {
public:
    bool isPerfectSquare(int num) {
        long root = num;
        while (root * root > num) 
            root = (root + num / root) / 2;
            
        return root * root == num;
    }
};
