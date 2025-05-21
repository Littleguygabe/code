data Expr = Val Int
    |Mul Expr Expr
    |Add Expr Expr

expr2int :: Expr -> Int
expr2int (Val n) = n
expr2int (Add x y) = expr2int x + expr2int y
expr2int (Mul x y) = expr2int x * expr2int y

main :: IO()
main = do
    print "hello world"