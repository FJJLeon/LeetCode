#include<util/tree.cpp>
#include<vector>
#include<queue>

using namespace std;


/**
 * iterative
 * 
 * use queue save level order treeNode
 * for each level, record the size of queue before traversing so that we can know when to stop this level traverse
 * use a boolean variable as zigzag flag
 * 
 * Runtime: 4 ms, faster than 81.35%, O(N)
 * Memory Usage: 12.6 MB, less than 18.30%, O(N)
*/
class SolutionA1 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root)
            return vector<vector<int>>();
        
        vector<vector<int>> res;
        
        queue<TreeNode*> q;
        q.push(root);
        bool zigzag = true;
        
        while (!q.empty()) {
            // record the size of queue
            int levelsize = q.size();
            vector<int> level;
            // get top [levelsize] treeNode for this level
            for (int i = 0; i < levelsize; ++i) {
                TreeNode *n = q.front();
                q.pop();
                // zigzag, zig -> push_back, zag -> insert begin
                if (zigzag) {
                    level.push_back(n->val);
                }
                else {
                    level.insert(level.begin(), n->val);
                }
                // next level
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
            }
            // change zigzag flag
            zigzag = !zigzag;
            res.push_back(level);
        }
        
        return res;
    }
};

/**
 * an optim for A, the size of level vector is known
 * 
 * Runtime: 4 ms, faster than 81.35%
 * Memory Usage: 12.1 MB, less than 96.10%
 * 
 * no number improve though
*/
class SolutionA {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root)
            return vector<vector<int>>();
        
        vector<vector<int>> res;
        
        queue<TreeNode*> q;
        q.push(root);
        bool zigzag = true;
        
        while (!q.empty()) {
            int levelsize = q.size();
            // the size of level vector is known
            vector<int> level(levelsize);
            for (int i = 0; i < levelsize; ++i) {
                TreeNode *n = q.front();
                q.pop();
                // get the index of the elem according to zigzag flag
                int index = zigzag ? i : (levelsize - i - 1);
                level[index] = n->val;
                
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
            }
            
            zigzag = !zigzag;
            res.push_back(level);
        }
        
        return res;
    }
};


/**
 * Recursive DFS
 * 
 * recursive with level and result vector(also can be private variable)
 * if new level entered, push new level vector to result vector
 * use level to know zig or zag
 * 
 * Runtime: 4 ms, faster than 81.35%, O(N)
 * Memory Usage: 12.9 MB, less than 7.30%, O(N+H)
*/
class SolutionB {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        dfs(root, 0, res);
        return res;
    }
private:
    // recursive with level and result vector
    void dfs(TreeNode* node, int level, vector<vector<int>>& v) {
        if (node == NULL) {
            return;
        }
        // new level entered
        if (v.size() == level) {
            v.push_back(vector<int>());
        }
        // use level for zigzag
        if (level % 2 == 0) {
            v[level].push_back(node->val);
        } else {
            v[level].insert(v[level].begin(), node->val);
        }
        // dfs
        dfs(node->left, level+1, v);
        dfs(node->right, level+1, v);
    } 
};

