grid :: Int ->[(Int,Int)]
grid n = [(x,y)| x<-[1..n] ,y <- [1..n], x/=y]