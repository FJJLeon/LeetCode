#include<bits/stdc++.h>

using namespace std;

// helper functions
int isSymbol(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

int priority(char c) {
	switch (c)
	{
		case '*':
		case '/':return 1;
		case '+':
		case '-':return 0;
		default: return -1;
	}
}

int comparePri(char x, char y) {
	return priority(x) > priority(y) ? 1 : 0;
}

string addBracket(string s) {
	return "("+s+")";
}

// convert Postfix expression to Expression tree
struct TreeNode {
	char val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(char x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* Post2Tree(string str) {    
	stack<TreeNode*> s;
	
	int len = str.length();
	for (int i=0; i<len; i++) {
		char c = str[i];
		/* 符号是数字 */
		if ( !isSymbol(c)) {
			TreeNode *tmp = new TreeNode(c);
            s.push(tmp);
		}
        /* 符号是运算符 */
        else {
            // 弹出两个数字
            TreeNode *b = s.top();
            s.pop();

            TreeNode *a = s.top();
            s.pop();
            // 创建表达式计算节点
            TreeNode *cal = new TreeNode(c);
            cal->left = a;
            cal->right = b;
            s.push(cal);
        }
	}

    TreeNode *root = s.top();
    s.pop();
    
    return root;
}

// convert Expression tree to Infix expression
// add parentheses when necessary
string Tree2Infix(TreeNode *root) {
    string res = "";
    string l, r;

    if (root) {
        l = Tree2Infix(root->left);
        r = Tree2Infix(root->right);

        if (root->left) {
            if (isSymbol(root->left->val) && comparePri(root->val, root->left->val)) {
                l = addBracket(l);
            }
        }

        if (root->right) {
            if (isSymbol(root->right->val) && !comparePri(root->right->val, root->val)) {
                r = addBracket(r);
            }
        }

        res = l + root->val + r;
    }

    return res;
}

// navie test
int main() {
	string s = "2963/+5-*4+";
    
    TreeNode *root = Post2Tree(s);
    
    cout << Tree2Infix(root);
	return 0;
}
