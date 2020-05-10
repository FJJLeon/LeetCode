#include<vector>
#include<set>

using namespace std;

/**
 * construct a directed graph for each pair of trust, pair[0] -> pair[1]
 * find the node whose in-degree == N-1 and out-degree == 0
 * 
 * Runtime: 372 ms, faster than 18.48%, O(2N+M), M = trust.size()
 * Memory Usage: 61.6 MB, less than 12.50%, O(N)
*/
class Solution11 {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int> inDegree(N+1);
        set<int> candidate;
        // candidate initialized to all people
        for (int i = 1; i <= N; ++i) {
            candidate.insert(i);
        }
        // for t[0] trust t[1]
        for (auto& t : trust) { 
            // increse t[1] inDegree
            ++inDegree[t[1]];
            // reomve t[0] from candidate
            candidate.erase(t[0]);
        }
        // for each candidate
        for (int c : candidate) {
            // check whether all other people trust candidate
            if (inDegree[c] == N - 1) {
                return c;
            }
        }
        return -1;
    }
};
/**
 * not as good to use two vector
 *      peoblem may come from how to initialize candidate set
 * Runtime: 356 ms, faster than 23.27%, O(N+M)
*/
class Solution12 {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int> inDegree(N+1);
        vector<int> outDegree(N+1);
        // for t[0] trust t[1]
        for (auto& t : trust) { 
            // increse t[1] inDegree and t[0] outDegree
            ++inDegree[t[1]];
            ++outDegree[t[0]];
        }
        // for each candidate
        for (int c = 1; c <= N; ++c) {
            // check whether all other people trust candidate and candidate trusts nobody
            if (inDegree[c] == N - 1 && outDegree[c] == 0) {
                return c;
            }
        }
        return -1;
    }
};
