import System.IO

sumList :: [Int] -> Int
sumList [] = 0
sumList (x:xs) = x+ sumList xs

customReverse :: [a] -> [a]
customReverse [] = []
customReverse (x:xs) = customReverse xs ++ [x]

listLength :: [a] -> Int
listLength (x:xs) = foldr (\ x-> (+) 1) 1 xs

iseven :: Int -> Bool
iseven x = mod x 2 == 0

filterCustom :: (a -> Bool) -> [a] -> [a]
filterCustom f xs = [x | x<-xs,f x]

main :: IO()
main = do
    let list = [1,2,3,4,5,6]
    print (sumList list)
    print (customReverse list)
    print (listLength list)
    print (filterCustom iseven list)