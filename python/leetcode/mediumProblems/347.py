class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        numhash = {}
        answers  = []
        for num in nums:
            if num in numhash:
                numhash[num]+=1

            else:
                numhash[num]=1

        z= sorted(numhash.values(),reverse = True)[k-1]
        for num in numhash:
            if numhash[num]>=z:
                answers.append(num)

            else:
                continue
        return answers