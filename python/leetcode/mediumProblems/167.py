class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        numHash = {}
        n = len(numbers)

        for i in range(n):
            numHash[numbers[i]] = i

        for i in range(n):
            complement = target - numbers[i]
            if complement in numHash and numHash[complement]!=i:
                return i+1,numHash[complement]+1