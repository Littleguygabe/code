import Control.Concurrent (getChanContents)
main :: IO ()
main = do
    putStrLn "Enter a char"
    c <- getChar
    putChar c

    