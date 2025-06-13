def getQfunction(algoType):
    def bfsQueing():
        print('bfs Q')

    def dfsQueing():
        print('dfs Q')

    if algoType == 'bfs':
        return bfsQueing
    elif algoType == 'dfs':
        return dfsQueing
    else:
        raise ValueError("algoType must be either 'bfs' or 'dfs'")

def runAlgo(algoType):
    qFunc = getQfunction(algoType)



class Node():
    def __init__(self,data) -> None:
        self.data = data
        self.left = None
        self.right = None




algoType = 'bfs'


#rear
# r l l

# r 