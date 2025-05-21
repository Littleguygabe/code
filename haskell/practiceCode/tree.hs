data Tree a = Empty | Node a (Tree a) (Tree a)

treeDepth :: Tree a -> Int
treeDepth Empty = 0  -- Base case: the depth of an empty tree is 0
treeDepth (Node _ left right) = 1 + max (treeDepth left) (treeDepth right) -- Recursive case