from treeStructure import Tree
import numpy as np

def minimax(position, depth, alpha, beta, maximisingPlayer):
    if depth == 0 or (position.left is None and position.right is None):
        return position.val

    if maximisingPlayer:
        maxEval = -np.inf
        for child in [position.left, position.right]:
            if child is None:
                continue
            eval = minimax(child, depth - 1, alpha, beta, False)
            maxEval = max(maxEval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                print(f'pruned branch with val: {position.val} at depth: {depth}')
                break  
        return maxEval

    else:
        minEval = np.inf
        for child in [position.left, position.right]:
            if child is None:
                continue
            eval = minimax(child, depth - 1, alpha, beta, True)
            minEval = min(minEval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                print(f'pruned branch with val: {position.val} at depth: {depth}')
                break  
        return minEval

def main():
    myTree = Tree(5)
    myTree.printTree()
    minMaxEval = minimax(myTree.root,5,-np.inf,np.inf,True)
    print(minMaxEval)



if __name__ == '__main__':
    main()