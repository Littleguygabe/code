myOr :: Bool -> Bool -> Bool

{-
myOr True True = True
myOr True False = True
myOr False True = True
myOr False False = False
-}

{-
myOr True  _ = True
myOr _ True = True
myOr False False = False
-}

{-
myOr False False = False
myOr _ _ = True
-}    