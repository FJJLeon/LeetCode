#include<vector>
#include<algorithm>

using namespace std;


/**
 * idea
 * 1. get the count of each number, get the max_count (for task E)
 * 2. greedy to schedule tasks
 *      a. schedule [max_count - 1] group tasks starting with E
 *      b. each group owns [n + 1] slots, n for cooldown time and 1 for task E
 *      c. if there exists more than one max_count task, we shoule schedule it at the end of last group
 *      d. so the slots number is [max_count - 1] * [n + 1] + [1 + other task occurrences same as max_count]
 * 3. however, if the slots number is not enough for tasks number, just return tasks number
 *      like case AAABBBCCCDD with n = 2, slots = [3(max_count) - 1] * [2(n) + 1] + [1 + 2(other)] = 9
 *      but 9 < 11(tasks number), just return 11
 * 
 * Runtime: 156 ms, faster than 65.30%, O(N)
 * Memory Usage: 34.5 MB, less than 67.90%, O(1)
*/
class Solution1 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        int max_count = 0;
        for (char t : tasks) {
            count[t - 'A']++;
            max_count = max(max_count, count[t - 'A']);
        }
        
        int slots = (max_count - 1) * (n + 1);
        for (int c : count) {
            if (c == max_count)
                slots++;
        }
        return max(slots, (int)tasks.size());
    }
};
