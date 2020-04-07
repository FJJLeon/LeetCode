#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

/**
 * use map: key - vecotr of char count --> value - corresponding anagrams
 * 
 * Runtime: 96 ms, faster than 16.98%, O(NK), N = len(strs), K = len(str)
 * Memory Usage: 23.3 MB, less than 17.91%, O(NK)
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // if unordered_map, hashfunc should be self-designed
        map<vector<int>, vector<string>> m;
        for (auto& str : strs) {
            vector<int> v(26);
            for (char c : str)
                v[c-'a']++;
            m[v].push_back(str);
        }
        vector<vector<string>> res;
        for (auto& p : m) {
            res.push_back(p.second);
        }
        return res;
    }
};


/**
 * use bucket sorted str as key, then we can use unordered_map without impl own hashfunc
 * map: key - sorted str --> value - index in result anagrams
 * 还有不少奇淫巧计都用在设置更NB的 key 上面了
 * 比如有把 string 用质数对应累乘转换成 int 的操作，还有把 occurrence 数组转换成 string 的
 * 
 * Runtime: 84 ms, faster than 21.73%, O(NK), note: 如果用内置 sort 的话，O(T) = O(NKlogK), 然而在LC测得的 runtime 似乎不稳定（或者有问题）
 * Memory Usage: 15.6 MB, less than 100.00%, O(NK)
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // key: sorted str, value: index in result anagrams
        unordered_map<string, int> index;
        vector<vector<string>> res;
        
        for (auto& str : strs) {
            // use sorted str as key
            string key = getKey(str);
            // push exectly into res, without copy again
            auto it = index.find(key);
            if (it != index.end())
                res[it->second].push_back(str);
            else {
                index[key] = res.size();
                res.push_back(vector<string>{str});
            } 
        }
        
        return res;
    }
private:
    inline string getKey(string str) {
        // bucket sort for string only [a-z]
        int count[26] = {0};
        for (char c : str) {
            count[c-'a']++;
        }
        string key;
        for (int i = 0; i < 26; ++i) {
            key += string(count[i], 'a' + i);
        }
        return key;
    }
};
