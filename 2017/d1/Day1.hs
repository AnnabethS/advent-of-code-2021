{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use let" #-}
module Day1 where
import Data.Char (digitToInt)

main :: IO ()
main = do
    inp <- readFile "input.txt"
    inp <- pure $ parse inp
    part1result <- pure $ part1 inp
    part2result <- pure $ part2 inp
    putStrLn $ "part1: " ++ show part1result
    putStrLn $ "part2: " ++ show part2result

parse :: String -> [Int]
parse = map digitToInt

part1 :: [Int] -> Int
part1 xs = sum . map fst . filter (uncurry (==)) $ zip ys (tail ys)
    where ys = take (1 + length xs) $ cycle xs

part2 :: [Int] -> Int
part2 xs = sum $ map fst $ filter (uncurry (==)) $ zip xs (take (length xs) $ drop ((length xs) `div` 2)  $ cycle xs)
