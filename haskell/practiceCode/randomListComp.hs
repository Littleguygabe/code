pairIsEven :: [Int] -> [(Int,Bool)]
pairIsEven list = [(x,even x) | x<-list]

main::IO()
main = do
    let testList = [1,2,3,4,5,6]
    print (pairIsEven testList)