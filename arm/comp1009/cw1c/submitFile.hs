second1 :: [a] -> a
second1 xs = head (tail xs)

second2 :: [a] -> a
second2 xs = xs !! 1 {- retrieves the item at index 1 (0 based indexing) -}

second3 :: [a] -> a
second3 (_:x:_) = x

xor1 :: Bool -> Bool -> Bool
xor1 True False = True
xor1 False True = True
xor1 _ _ = False

xor2 :: Bool -> Bool -> Bool
xor2 a b = if a == b then False else True

xor3 :: Bool -> Bool -> Bool
xor3 a b = a/=b

sumsqr :: Int -> Int
sumsqr n = sum [x^2 | x <- [1..n]]

grid :: Int ->[(Int,Int)]
grid n = [(x,y)| x<-[1..n] ,y <- [1..n], x/=y]

euclid :: Int -> Int -> Int
euclid a b
  | a == b    = a
  | a > b     = euclid (a - b) b
  | otherwise = euclid a (b - a)

fastrev :: [a] -> [a]
fastrev xs = rev xs []

rev :: [a] -> [a] -> [a]
rev [] ys = ys
rev (x:xs) ys = rev xs (x:ys)

