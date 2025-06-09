# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxDepth(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """

        def helper(root,count):
            if root!=None:
                if not root.left and not root.right:
                    return count+1

                return max(helper(root.left,count+1),helper(root.right,count+1))

            return 0

        return helper(root,0)