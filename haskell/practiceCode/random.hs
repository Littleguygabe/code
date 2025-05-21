

data Nat = Zero|Succ Nat

int2nat :: Int -> Nat
int2nat 0 = Zero
int2nat n = Succ (int2nat (n-1))  

let Nat natNum1 = int2nat 5
let Nat natNum2 = int2nat 3


