-- zip the ys and xs together into pairs
-- then multiply each pair and return a list of the products
-- then sum the returned list to get the scalar product

scalarProd :: [Int] -> [Int] -> Int
scalarProd xs ys = sum [x*y | (x,y) <- zip xs ys]