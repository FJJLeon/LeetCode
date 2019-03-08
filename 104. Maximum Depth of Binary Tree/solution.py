# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# Runtime: 52 ms
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        # recursion version
        if not root:
            return 0
        else:
            return max(self.maxDepth(root.left), self.maxDepth(root.right)) + 1

# Runtime: 92 ms
class Solution1:
    def maxDepth(self, root: TreeNode) -> int:
        # iteration version BFS using queue
        res = 0
        import queue
        q = queue.Queue()
        if root:
            q.put((root, 0))
        while(not q.empty()):
            tmpNode, fatherDepth = q.get()
            if fatherDepth + 1 > res:
                res = fatherDepth + 1
            if tmpNode.left: 
                q.put((tmpNode.left, fatherDepth + 1))
            if tmpNode.right: 
                q.put((tmpNode.right, fatherDepth + 1))
        return res

# Runtime: 48 ms
class Solution2:
    def maxDepth(self, root: TreeNode) -> int:
        # iteration version DFS using list as stack
        res = 0
        stack = [(root, 0)] if root else []
        while(len(stack) != 0):
            tmpNode, fatherDepth = stack.pop()
            if fatherDepth + 1 > res:
                res = fatherDepth + 1
            if tmpNode.left: 
                stack.append((tmpNode.left, fatherDepth + 1))
            if tmpNode.right: 
                stack.append((tmpNode.right, fatherDepth + 1))
        return res
