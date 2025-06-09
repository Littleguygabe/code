class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        newx = int(str(abs(x))[::-1])
        
        if x<0:
            newx *=-1
        
        if newx<-(2**31) or newx>(2**31-1):
            return 0

        return newx