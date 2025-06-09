class Solution:
    def trap(self, height: List[int]) -> int:
        l,r = 0,len(height)-1
        leftMax,rightMax = height[l],height[r]
        
        vol = 0

        while l<r:
            if leftMax>rightMax:
                r-=1
                rightMax = max(rightMax,height[r])
                vol+= rightMax-height[r]
            else:
                l+=1
                leftMax = max(leftMax,height[l])
                vol += leftMax-height[l]

        return vol