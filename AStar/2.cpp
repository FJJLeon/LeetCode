#include<iostream>
#include<limits.h>
#include<assert.h>
#include<vector>
#include<algorithm>

double gpa(int s) {
    assert(s >= 0 && s <= 100);
    if (s >= 95) {
        return 4.3;
    }
    else if (s >= 90) {
        return 4.0;
    }
    else if (s >= 85) {
        return 3.7;
    }
    else if (s >= 80) {
        return 3.3;
    }
    else if (s >= 75) {
        return 3.0;
    }
    else if (s >= 70) {
        return 2.7;
    }
    else if (s >= 67) {
        return 2.3;
    }
    else if (s >= 65) {
        return 2.0;
    }
    else if (s >= 62) {
        return 1.7;
    }
    else if (s >= 60) {
        return 1.0;
    }
    else {
        return 0;
    }
}

int main() {
    std::vector<double> v(101);
    for (int i = 0; i <= 100; ++i) {
        v[i] = gpa(i);
    }

    int t;
    std::cin >> t;
    while (t--) {
        int x;
        std::cin >> x;
        if (x < 60) {
            printf("%.1f\n", 0);
            continue;
        }

        int a,b,c,d;
        double res = 0, tmp;
        for (a = 0; a <= 100 && a <= x; ++a) {
            for (b = 0; b <= 100 && a + b <= x; ++b) {
                for (c = 0; c <= 100 && a + b + c <= x; ++c) {
                    d = x - a - b - c;
                    if (d > 100)
                        continue;                        
                    tmp = v[a] + v[b] + v[c] + v[d];
                    res = std::max(res, tmp);
                }
            }
        }

        printf("%.1f\n", res);
    }

    return 0;
}