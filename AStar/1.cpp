#include<iostream>
#include<limits.h>
#include<algorithm>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        
        int res = INT_MAX;
        while (n--) {
            int x, y;
            std::cin >> x >> y;

            int a = m / x, b = m % x;
            a += (b == 0) ? 0 : 1;
            res = std::min(res, a * y);
        }
        std::cout << res << std::endl;
    }

    return 0;
}