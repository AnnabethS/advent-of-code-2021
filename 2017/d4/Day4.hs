module Day4 where
import Data.List

main :: IO ()
main = do
    inp <- readFile "input.txt"
    inp <- pure $ lines inp
    inp <- pure $ map words inp
    part1result <- pure $ part1 inp
    part2result <- pure $ part2 inp
    putStrLn $ "part1: " ++ show part1result
    putStrLn $ "part2: " ++ show part2result


part1 :: [[String]] -> Int
part1 = length . filter (\xs -> length xs == length  (nub xs))


part2 :: [[String]] -> Int
part2 xs = length $ filter (\xs -> length xs == length  (nub xs)) ys
    where
        ys :: [[String]]
        ys = map (map sort) xs
