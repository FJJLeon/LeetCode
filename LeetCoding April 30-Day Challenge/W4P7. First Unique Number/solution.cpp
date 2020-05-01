#include<vector>
#include<queue>
#include<set>
#include<unordered_map>

using namespace std;

/**
 * allSet record all number appeared
 * uniqueSet record all unique number appeared
 * q maintain FIFO number order
 * 
 * Runtime: 936 ms
 * Memory Usage: 99.8 MB
*/
class FirstUnique {
public:
    FirstUnique(vector<int>& nums) {
        for (int n : nums) {
            q.push(n);
            // not appear yet
            if (allSet.find(n) == allSet.end()) {
                allSet.insert(n);
                uniqueSet.insert(n);
            }
            // already appear
            else {
                uniqueSet.erase(n);
            }
        }
        while (!q.empty() && uniqueSet.find(q.front()) == uniqueSet.end()) {
            q.pop();
        }
    }
    
    int showFirstUnique() {
        return q.empty() ? -1 : q.front();
    }
    
    void add(int value) {
        q.push(value);
        if (allSet.find(value) == allSet.end()) {
            allSet.insert(value);
            uniqueSet.insert(value);
        }
        else {
            uniqueSet.erase(value);
            while (!q.empty() && uniqueSet.find(q.front()) == uniqueSet.end())
                q.pop();
        }
    }
private:
    set<int> uniqueSet, allSet;
    queue<int> q;
};

/**
 * unordered_map allMap replace two set, record number occurrence
 * 
 * Runtime: 468 ms
 * Memory Usage: 80.1 MB
*/
class FirstUnique {
public:
    FirstUnique(vector<int>& nums) {
        for (int n : nums) {
            ++allMap[n];
            q.push(n);
        }
    }
    
    int showFirstUnique() {
        // remove duplicate number as FIFO order before show
        while (!q.empty() && allMap[q.front()] > 1)
            q.pop();
        return q.empty() ? -1 : q.front();
    }
    
    void add(int value) {
        ++allMap[value];
        q.push(value);
    }
private:
    unordered_map<int, int> allMap;
    queue<int> q;
};


/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */