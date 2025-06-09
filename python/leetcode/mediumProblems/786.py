class Solution:
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        count = 0
        fracs = {}
        while count<len(arr):
            for num in arr:
                frac = arr[count]/num
                val = (arr[count],num)
                if frac not in fracs and frac<1:
                    fracs[frac] = val
            count+=1

        return (list(fracs[sorted(fracs)[k-1]]))