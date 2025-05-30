from treeStructure import Tree
import numpy as np


def minimax(position,depth,maximisingPlayer):
    if depth == 0 or (position.left == None and position.right == None):
        return position.val
    
    #if the maximising player is player 1
    if maximisingPlayer:
        leftEval = minimax(position.left,depth-1,False)
        rightEval = minimax(position.right,depth-1,False)
        maxEval = max(-np.inf,leftEval,rightEval)
        return maxEval
    

    else:
        leftEval = minimax(position.left,depth-1,True)
        rightEval = minimax(position.right,depth-1,True)
        minEval = min(np.inf,leftEval,rightEval)
        return minEval
    
def main():
    myTree = Tree(5)
    myTree.printTree()
    minMaxEval = minimax(myTree.root,5,True)
    print(minMaxEval)



if __name__ == '__main__':
    main()