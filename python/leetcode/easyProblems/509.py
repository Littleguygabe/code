class Solution:
    def fib(self, n: int) -> int:
        fibN = 1
        prevFibN = 0    
        if n == 0:
            return 0
        
        for i in range(n-1):
            temp = fibN
            fibN+=prevFibN
            prevFibN = temp
        return fibN