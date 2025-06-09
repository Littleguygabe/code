class Solution:
    def applyOperations(self, nums: List[int]) -> List[int]:
        arr2 = []
        count=0
        for i in range(0,len(nums)-1):
            if nums[i] == nums[i+1]:
                nums[i]*=2
                nums[i+1] = 0

        for num in nums:
            if num != 0:
                arr2.append(num)

            else:
                count+=1

        return arr2+[0]*count