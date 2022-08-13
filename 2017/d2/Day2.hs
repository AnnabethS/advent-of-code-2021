module Day2 where

import Data.List

main :: IO ()
main = do
    inp <- readFile "input.txt"
    inp <- pure $ parse $ lines inp
    part1result <- pure $ part1 inp
    part2result <- pure $ part2 inp
    putStrLn $ "part1: " ++ show part1result
    putStrLn $ "part2: " ++ show part2result


parse :: [String] -> [[Int]]
parse = map parseLine
    where
        parseLine :: String -> [Int]
        parseLine = map read . words

part1 :: [[Int]] -> Int
part1 = sum . map (\xs -> maximum xs - minimum xs)

part2 :: [[Int]] -> Int
part2 = sum . map doLine
    where
        doLine :: [Int] -> Int
        doLine = g . concat . filter f . filter ((==2) . length) . subsequences
        f [x,y] = ((x `mod` y) == 0) || ((y `mod` x) == 0)
        f _ = undefined
        g :: [Int] -> Int
        g xs = maximum xs `div` minimum xs
