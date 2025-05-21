xor1 :: Bool -> Bool -> Bool
xor1 True False = True
xor1 False True = True
xor1 _ _ = False

xor2 :: Bool -> Bool -> Bool
xor2 a b = if a == b then False else True

xor3 :: Bool -> Bool -> Bool
xor3 a b = a/=b