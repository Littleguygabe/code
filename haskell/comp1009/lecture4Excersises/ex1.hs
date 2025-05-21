safeTail :: [a] -> [a]
--using conditionals
-- safeTail xs = if (null xs) then [] else (tail xs) 

--using guarding
{- safeTail xs | null xs = []
            | otherwise = tail xs -}

--using pattern matching
safeTail [] = []
safeTail (_:xs) = xs