#include<bits/stdc++.h>

using namespace std;

/**
 * Sliding Window
 * 
 * mark window [b, e]
 * use map record occurrence times of each character between substr[b, e] when extend
 * when all {a, b, c} exist, [b, e] is valid substr, so as [0, e]
 * shrink window until invalid for [new b, e], then there are 'new b' valid substringsended with s[e] 
 * 
 * Runtime: 80 ms, 19.22%
 * Memory Usage: 10.2 MB, 100.00%
*/
class Solution11 {
public:
    int numberOfSubstrings(string s) {
        // record occurrence times of each character in SW
        map<char, int> m;
        
        int count = 0, len = s.length();
        // SW [b, e]
        for (int b=0, e=0; e<len; ++e) {
            m[s[e]]++;
            while (m['a'] > 0 && m['b'] > 0 && m['c'] > 0)
                m[s[b++]]--;
            count += b;
        }
        
        return count;
    }
};

/**
 * replace map with vector
 * 
 * faster, 数据量较小时 能用 vector 就别用 map， 效率更高
 * 
 * Runtime: 24 ms, 86.77%
 * Memory Usage: 9.8 MB, less than 100.00%
*/
class Solution12 {
public:
    int numberOfSubstrings(string s) {
        vector<int> v(3);
        
        int count = 0, len = s.length();
        for (int b=0, e=0; e<len; ++e) {
            v[s[e] - 'a']++;
            while (v[0] > 0 && v[1] > 0 && v[2] > 0)
                v[s[b++] - 'a']--;
            count += b;
        }
        
        return count;
    }
};


/**
 * 仅维护每个字符出现的最后 index
 * 类似 SW 的说法
 * 设各个字符出现的最后 index 中的最小值为 min, [min, i] 是一个合法 substr，那么 [0, i] 也是，共有 min + 1 个
 * 
 * 每个做法都是去统计 SW 和 SW 之前的，而不是像我考虑的 SW 之后的，需要注意
 * 
 * Runtime: 20 ms, 96.74%
 * Memory Usage: 10.2 MB, 100%
*/
class Solution12 {
public:
    int numberOfSubstrings(string s) {
        // record last occurrence index
        vector<int> last(3, -1);
        
        int count = 0, len = s.length();
        for (int i=0; i<len; ++i) {
            last[s[i] - 'a'] = i;
            count += min(min(last[0], last[1]), last[2]) + 1;
        }
        
        return count;
    }
};
