#include<iostream>
#include<limits.h>
#include<algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        double p;
        cin >> p;
        if (p > 1)
            cout << "No" << endl;
        else 
            cout << "Yes" << endl;
    }
    return 0;
}