
def minimiseMax(nums,p):
    ns = sorted(nums)
    r = abs(ns[0]-ns[-1])
    

nums = [4,5,4,0,4,3,2]
p = 3
print(minimiseMax(nums,p))