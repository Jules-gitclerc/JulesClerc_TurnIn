
addIntegers :: Integer -> Integer -> Integer
addIntegers x y = x + y

main:: IO()
main = do

-- This "putstr" command will do whatever you tell the teleprompter to write immediately --
putStr "Sum of x + y = "
print(addIntegers 5 6)