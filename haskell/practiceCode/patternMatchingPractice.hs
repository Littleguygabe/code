import System.IO

isPalindrome :: Eq a => [a] -> Bool
isPalindrome xs = xs == reverse xs  

productList :: [Int] -> Int
productList xs = foldr (*) 1 xs

main :: IO()
main = do
    let list = [1,2,3,4,5,6]
    print list
    print (isPalindrome list)
    print (productList list)