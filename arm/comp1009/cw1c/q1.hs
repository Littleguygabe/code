second1 :: [a] -> a
second1 xs = head (tail xs)

second2 :: [a] -> a
second2 xs = xs !! 1 {- retrieves the item at index 1 (0 based indexing) -}

second3 :: [a] -> a
second3 (_:x:_) = x