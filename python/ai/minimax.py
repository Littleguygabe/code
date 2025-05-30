import numpy as np
import random
from dataclasses import dataclass
from typing import Optional


@dataclass
class Node:
    val:int
    left:Optional['Node'] = None
    right:Optional['Node'] = None



def createTree():
    def constructor(count):
        if count == 0:
            return None
        
        node = Node(random.randint(1,9))
        node.left = constructor(count-1)
        node.right = constructor(count-1)

        return node 

    root = constructor(3)

    return root

def printTree(node, level=0):
    if node is not None:
        print('  ' * level + f'Node(val={node.val})')
        printTree(node.left, level + 1)
        printTree(node.right, level + 1)


def main():
    testTree = createTree()
    printTree(testTree)



if __name__ == '__main__':
    main()