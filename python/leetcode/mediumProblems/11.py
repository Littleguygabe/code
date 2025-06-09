class Solution:
    def maxArea(self, height: List[int]) -> int:
        l,r = 0,len(height)-1
        maxVol = 0  
        while l<r:
            vol = min(height[l],height[r])*(r-l)
            maxVol = max(vol,maxVol)
            if height[l]<height[r]:
                l+=1
            else:
                r-=1
        return maxVol