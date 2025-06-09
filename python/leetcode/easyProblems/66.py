class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        dstr = ''
        arr = []
        for d in digits:dstr +=str(d)
        dstr = str(int(dstr)+1)
        for i in dstr: arr.append(int(i))
        return arr