class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        points = 0
        stack = []
        if x>=y:
            priority = 'ab'
            priorityScore = x
            second = 'ba'
            npScore = y
        else:
            priority = 'ba'
            priorityScore = y
            second = 'ab'
            npScore = x


        for i in s:
            if len(stack)!=0:
                if stack[-1]+i == priority:
                    stack.pop()
                    points+=priorityScore
                else:
                    stack.append(i)
            else:
                stack.append(i)

        s = ''.join(stack)
        stack = []

        for i in s:
            if len(stack)!=0:
                if stack[-1]+i == second:
                    stack.pop()
                    points+=npScore
                else:
                    stack.append(i)
            else:
                stack.append(i)
        return points