removeDuplicates :: Eq a => [a] -> [a]
removeDuplicates [] = []
removeDuplicates (x:y:xs)   | x == y    = x:removeDuplicates xs
                            | otherwise = x:removeDuplicates (y:xs)


                            