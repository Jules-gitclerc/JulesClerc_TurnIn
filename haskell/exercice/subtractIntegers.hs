
subtractIntegers :: Integer -> Integer -> Integer
subtractIntegers x y = x - y

main:: IO()
main = do

-- This "putstr" command will do whatever you tell the teleprompter to write immediately --
putStr "Sum of x + y = "
print(subtractIntegers 5 6)