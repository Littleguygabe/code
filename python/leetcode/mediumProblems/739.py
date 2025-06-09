class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
         
        res = [0] * len(temperatures)
        stack = [] # store value and index [val,index]

        for i,t in enumerate(temperatures):
            while stack and t>stack[-1][0]:
                temp,tInd = stack.pop()
                res[tInd] = (i-tInd)

            stack.append([t,i])

        return res
