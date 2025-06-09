class Solution:
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        i = 0

        if len(chalk) == 1:
            return 0

        k = k%sum(chalk)

        while True:
            k-=chalk[i%(len(chalk))]
            if k<0:
                return i%(len(chalk))
            i+=1