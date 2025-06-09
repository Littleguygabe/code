# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isSymmetric(self,root):
        def isMirror(q,p):

            if not q and not p:
                return True
            if not q or not p:
                return False

            return(
                q.val == p.val
                and isMirror(q.right,p.left)
                and isMirror(q.left,p.right)
            )

        return isMirror(root,root)