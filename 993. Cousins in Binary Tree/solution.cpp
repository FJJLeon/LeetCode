#include"util/tree.cpp"
#include<queue>

using namespace std;

/**
 * iterative level traverse construct Relation for x and y
 * 
 * Runtime: 4 ms, faster than 67.92%, O(N)
 * Memory Usage: 11.1 MB, less than 100.00%, O(N)
*/
class Solution11 {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<Relation *>  q;
        Relation *xr = NULL, *yr = NULL;
        q.push(new Relation(root, 0, NULL));
        
        while (!q.empty()) {
            Relation* r = q.front();
            q.pop();
            if (r->cur->val == x)
                xr = r;
            if (r->cur->val == y)
                yr = r;
            if (r->cur->left)
                q.push(new Relation(r->cur->left, r->depth + 1, r->cur));
            if (r->cur->right)
                q.push(new Relation(r->cur->right, r->depth + 1, r->cur));
            if (xr != NULL && yr != NULL)
                break;
        }
        
        return xr != NULL && yr != NULL &&
            xr->depth == yr->depth && xr->parent != yr->parent; // same depth, different parent
    }
private:
    struct Relation {
        TreeNode* cur;      // current TreeNode
        int depth;          // depth
        TreeNode* parent;   // its parent TreeNode
        Relation(TreeNode* c, int d, TreeNode* p) : cur(c), depth(d), parent(p) {} 
    };
};

/**
 * Recursive dfs traverse
 * recursive function need take parent and depth as arguments
 * set class private relation for x, y while traversing
 * 
 * Runtime: 4 ms, faster than 67.92%, O(N)
 * Memory Usage: 11 MB, less than 100.00%, O(H)
*/
class Solution12 {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        xDep = yDep = -1;
        xPar = yPar = NULL;
        traverse(root, x, y, 0, NULL);
        return xDep == yDep && xPar != yPar;
    }
private:
    int xDep, yDep;
    TreeNode *xPar, *yPar;
    void traverse(TreeNode* root, int x, int y, int depth, TreeNode* parent) {
        // include early stop
        if (!root || (xDep != -1 && yDep != -1))
            return;
        // check x, y and set private relation
        if (x == root->val)
            xDep = depth, xPar = parent;
        if (y == root->val)
            yDep = depth, yPar = parent;
        // dfs
        traverse(root->left, x, y, depth + 1, root);
        traverse(root->right, x, y, depth + 1, root);
    }
};
