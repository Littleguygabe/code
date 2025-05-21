applyNTimes :: (a->a) -> a -> Int -> a
applyNTimes _ a 0 = a
applyNTimes f x n = f (applyNTimes f x (n-1))