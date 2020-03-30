#include"util/tree.cpp"
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<queue>
#include<sstream>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * stright forward, DFS + HashMap count subtree sum freq
 * 
 * Runtime: 20 ms, faster than 84.30%
 * Memory Usage: 21.8 MB, less than 100.00%
*/
class Solution1 {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        int rootSum = postorderSum(root);
        
        vector<int> res;
        int maxfreq = 0;
        for (auto& p : f) {
            if (p.second > maxfreq) {
                res = vector<int>{p.first};
                maxfreq = p.second;
            }
            else if (p.second == maxfreq) {
                res.push_back(p.first);
            }
        }
        return res;
    }
private:
    unordered_map<int, int> f;
    int postorderSum(TreeNode* root) {
        if (!root)
            return 0;
        int left = 0, right = 0, sum;
        if (root->left) {
            left = postorderSum(root->left);
        }
        if (root->right) {
            right = postorderSum(root->right);
        }
        sum = left + root->val + right;
        f[sum] = f[sum] ? f[sum] + 1 : 1;
        return sum;
    }
};

/**
 * Simplify code
*/
class Solution2 {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        int rootSum = postorderSum(root);
        
        vector<int> res;
        for (auto& p : freq) {
            if (p.second == maxfreq) {
                res.push_back(p.first);
            }
        }
        return res;
    }
private:
    unordered_map<int, int> freq;
    int maxfreq = 0;
    
    int postorderSum(TreeNode* root) {
        if (!root)
            return 0;
        int sum = postorderSum(root->left) + root->val + postorderSum(root->right);
        freq[sum] = freq[sum] ? freq[sum] + 1 : 1;
        maxfreq = max(maxfreq, freq[sum]);
        return sum;
    }
};