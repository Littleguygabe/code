class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        numHash = {}
        n = len(nums)

        for i in range(n):
            numHash[nums[i]] = i