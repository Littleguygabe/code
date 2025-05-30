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
    n = random.randint()


def main():
    testTree = createTree()




if __name__ == '__main__':
    main()