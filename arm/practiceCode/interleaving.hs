interleave :: [a] -> [a] -> [a]
interleave [] [] = []
interleave [] ys = ys
interleave xs [] = xs
interleave (x:xs) (y:ys) = x : y : interleave xs ys