import Data.Char (digitToInt)

printStars :: Int -> IO()
printStars n = do
        if n == 0 then
            putChar '\n'
            
        else do
            putStr " *"
            printStars (n-1)

printTableNum :: Int -> IO()
printTableNum n = putStr (show n ++ ":")
   
displayTable :: Int -> [Int] -> IO()
dsplayTable 0 _ = putStrLn ""
displayTable _ [] = putStrLn ""

displayTable i (x:xs) = do
    printTableNum i
    printStars x
    displayTable (i+1) xs

removeToken :: Int -> [Int] -> [Int]
removeToken i xs = zipWith (\idx val -> if idx == i then val - 1 else val) [0..] xs


playTurn :: [Int] -> IO()

playTurn [] = do
    putStrLn "Game Finished"

playTurn table = do 
    displayTable table
    putStrLn "Enter a row to play on"
    row <- digitToInt getChar
    playTurn (removeToken row Table)


main :: IO()
main = do
    let table = [5,4,3,2,1]
    displayTable 1 table
    startGame table
    putStrLn "finished execution"
