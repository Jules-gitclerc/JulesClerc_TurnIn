main = do
    let var = 0
    if var == 0
        then putStrLn "var is 0"
    else if even var
        then putStrLn "var is even"
    else putStrLn "var is odd"