import System.IO

splitCsv :: String -> [String]
splitCsv [] = []
splitCsv (x:xs)
    | x == ',' = []
    | otherwise = (x : head (splitCsv xs)) : tail (splitCsv xs)


parseCsv :: String -> [[String]]
parseCsv content = map splitCsv (lines content)

main :: IO ()
main = do
    content <- readFile "example.txt"
    let rows = parseCsv content
    print rows