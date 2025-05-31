import random
from collections import deque
from dataclasses import dataclass
from typing import Optional


class Tree:
    @dataclass
    class Node:
        val: int
        left: Optional['Tree.Node'] = None
        right: Optional['Tree.Node'] = None


    def __init__(self, depth) -> None:
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

    def printTree(self):
        """
        Prints the tree level by level (breadth-first traversal).
        """
        if not self.root:
            print("Tree is empty.")
            return

        queue = deque([(self.root, 0)]) # Store (node, level)
        current_level = 0
        level_nodes = []

        print("--- Tree Level by Level ---")
        while queue:
            node, level = queue.popleft()

            if level > current_level:

                print(f"{((self.depth-current_level)*2)*'  '}{('  '*(self.depth-current_level+1)).join(level_nodes)}")
                current_level = level
                level_nodes = []
            
            level_nodes.append(f"{node.val}")

            if node.left:
                queue.append((node.left, level + 1))
            if node.right:
                queue.append((node.right, level + 1))
        
        # Print the last level
        print(f"{((self.depth-current_level)*2)*'  '}{((self.depth-current_level+1)*'  ').join(level_nodes)}")


def main():
    testTree = Tree(3)
    testTree.printTree()


if __name__ == '__main__':
    main()
