class Solution(object):
    def minOperations(self, boxes):
        pos = []
        a = []
        ln = len(boxes)
        for i in range(ln):
            if boxes[i] == '1':
                pos.append(i)

        for i in range(ln):
            sm = 0
            for idx in pos:
                sm+=abs(i-idx)

            a.append(sm)

        return a