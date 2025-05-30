import random
from dataclasses import dataclass
from typing import Optional


class Tree:
    @dataclass
    class Node:
        val:int
        left:Optional['Tree.Node'] = None
        right:Optional['Tree.Node'] = None


    def __init__(self,depth) -> None:
        self.depth = depth
        self.root = self.createTree()

    def createTree(self):
        def constructor(count):
            if count == 0:
                return None
            
            node = self.Node(random.randint(1,9))
            node.left = constructor(count-1)
            node.right = constructor(count-1)

            return node 

        root = constructor(self.depth)

        return root

    def printTree(self,node=None, level=0):
        if node is None:
            node = self.root
        print('  ' * level + f'Node(val={node.val})')

        if node.left:
            self.printTree(node.left, level + 1)
        
        if node.right:
            self.printTree(node.right, level + 1)


def main():
    testTree = Tree(3)
    testTree.printTree()



if __name__ == '__main__':
    main()