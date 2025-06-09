# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def insertGreatestCommonDivisors(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        def gcd(a,b):
            while b:
                a,b=b,a%b

            return a

        node = head
        while node.next:
            #insert a new node between this node and the next node
            nextNode = node.next

            gcdValue = gcd(node.val,nextNode.val)

            newNode = ListNode(gcdValue)
            node.next=newNode
            newNode.next = nextNode

            node=nextNode

        return head
        