class Solution:
    def sortArrayByParity(self, nums: List[int]) -> List[int]:
        arr = []
        for num in nums: arr.insert(0,num) if num%2 == 0 else arr.append(num)
        return(arr)