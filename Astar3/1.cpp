#include<iostream>
#include<limits.h>
#include<algorithm>
#include <iomanip>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        double discount = 0;
        while (n--) {
            int b;
            double c;
            cin >> b >> c;
            
            double tmp = (1 - c) / (b + 1 - c);
            discount = max(discount, tmp);
        }
        discount = int(discount*100000 + 0.5) / 100000.0;
        printf("%.5f\n", discount);
    }
    return 0;
}