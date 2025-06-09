class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
            if len(matrix) == 0:
                return False
            for item in matrix:
                if target>item[-1]:
                    continue
                
                while True:
                    if len(item) == 1 and item[0] != target:
                        return False

                    if item[int(len(item)/2)] == target:
                        return True
                    
                    elif item[int(len(item)/2)]> target:
                        item = item[:int(len(item)//2)]
                    
                    else:
                        item = item[int(len(item)//2):]
