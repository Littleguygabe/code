class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
            if len(matrix) == 0:
                return False

            N,M = len(matrix),len(matrix[0])

            i,j = 0, len(matrix)-1
            while j>=0 and i<M:
                if matrix[j][i] == target:
                    return True

                elif matrix[j][i]>target:
                    j-=1
                elif matrix[j][i]<target:
                    i+=1

            return False