#include<vector>
#include<string>
#include<algorithm>
#include<unordered_set>

using namespace std;

/**
 * simulate to handle one by one
 * 
 * Runtime: 1608 ms, faster than 5.08%, O(N^2*K), K for length of word, so bad
 * Memory Usage: 13.3 MB, less than 100.00%, O(N*K)
*/
class Solution1a {
public:
    int minimumLengthEncoding(vector<string>& words) {
        // maintain current reference strings
        vector<string> encoder;
        
        int res = 0;
        for (string& w : words) {
            if (encoder.empty()) {
                encoder.push_back(w);
                res += w.size() + 1;
            }
            else {
                // flag for cannot masked string, need new reference string
                bool needNew = true;
                // check coming word w is suffix of exist reference string e or
                // exist reference string e is suffix of coming word w
                for (string& e : encoder) {
                    int elen = e.size(), wlen = w.size();
                    // check shorter word be suffix of longer word
                    bool refLonger = elen >= wlen;
                    string::size_type index = refLonger ? e.find(w) : w.find(e);

                    if (refLonger) {
                        // coming word w is suffix of exist reference string e
                        // no need update
                        if (index != string::npos && index == elen - wlen) {        // TODO: why this so strange
                            needNew = false;
                            break;
                        }
                    }
                    else {
                        // exist reference string e is suffix of coming word w
                        // replace e with w
                        if (index != string::npos && index == wlen - elen) {
                            needNew = false;
                            res += wlen - elen;
                            e = w;
                            break;
                        }
                    }
                }
                // need new reference string
                if (needNew) {
                    res += w.size() + 1;
                    encoder.push_back(w);
                }
            }
        }
        
        return res;
    }
};

/**
 * simplify code logic
 * sort words to make sure longer words appear first
 * 
 * Runtime: 1340 ms, faster than 5.08%
 * Memory Usage: 13.2 MB, less than 100.00%
*/
class Solution1b {
public:
    int minimumLengthEncoding(vector<string>& words) {
        // sort in descending order by string length
        sort(words.begin(), words.end(), [](const string& s1, const string& s2){
            return s1.size() > s2.size();
        });

        int len = words.size();
        vector<string> encoder;
        encoder.push_back(words[0]);
        int res = words[0].size() + 1;
        for (int i=1; i<len; ++i) {
            string w = words[i];

            bool needNew = true;
            for (string& e : encoder) {
                // sorted, so e.size > w.size
                string::size_type index = e.find(w);
                // w is suffix of e
                if (index != string::npos && index == e.size() - w.size()) {
                    needNew = false;
                    break;
                }
            }
            if (needNew) {
                res += w.size() + 1;
                encoder.push_back(w);
            }
        }
        
        return res;
    }
};

/**
 * use words construct a set
 * remove all suffix of each word from the set, at last the words in set in necessary for reference string
 * 
 * Runtime: 72 ms, faster than 59.89%, O(N*K^2)
 * Memory Usage: 13.6 MB, less than 100.00%, O(N*K)
*/
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> s(words.begin(), words.end());
        
        for (const string& w : s) {
            // for each string, remove all suffix
            for (int i=1; i<w.size(); ++i) {
                // set erase if not exist is ok
                s.erase(w.substr(i));
            }
        }
        
        int res = 0;
        for (const string& w : s) {
            res += w.size() + 1;
        }
        
        return res;
    }
};


// TODO Trie Tree