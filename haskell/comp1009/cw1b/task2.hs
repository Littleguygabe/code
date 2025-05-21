copy :: a -> a
copy x = x

one :: a -> [a]
one x = [x]

first :: (a,b) -> a
first (x,y) = x

second :: a -> b -> b 
second x y = y

mult :: Int -> Int -> Int 
mult m n = m*n