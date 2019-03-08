# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        if not root:
            return True
        return self.isMirror(root, root)
        
    def isMirror(self, n1, n2):
        if (n1 is None and n2 is None):
            return True
        elif (n1 and n2 and n1.val == n2.val):
            return self.isMirror(n1.left, n2.right) and self.isMirror(n1.right, n2.left)
        else:
            return False