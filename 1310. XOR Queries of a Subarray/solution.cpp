#include<vector>

using namespace std;

/**
 * Brute Force
 * 
 * Runtime: 1884 ms, O(M*N), M is length of queries, N is length of arr
 * Memory Usage: 28 MB
*/

class Solution1 {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> res;
        for (vector<int> q : queries) {
            int value = 0;
            for (int j=q[0]; j<=q[1]; j++) {
                value ^= arr[j];
            }
            res.push_back(value);
        }
        return res;
    }
};

/**
 * prefix XOR
 * XOR is commutative operation
 * XOR[L, R] = prefixXOR[L] ^ prefixXOR[R-1], R != 0, where prefixXOR[Z] = arr[0] xor arr[1] xor ... xor arr[Z]
 * 
 * Runtime: 128 ms, O(N+M)
 * Memory Usage: 25.5 MB
*/
class Solution2 {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {    
        // compute prefix xor
        int len = arr.size();
        vector<int> prefixXor(len+1, 0);
        for (int i=0; i<len; ++i) {
            prefixXor[i+1] = prefixXor[i] ^ arr[i];
        }
        // XOR[L, R] = prefixXOR[L] ^ prefixXOR[R-1], R != 0
        vector<int> res;
        for (vector<int> &q : queries) {
            res.push_back(prefixXor[q[1]+1]^prefixXor[q[0]]);
            
        }
        return res;
    }
};