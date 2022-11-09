module Day1 where
import Data.Maybe
import Data.List

main :: IO()
main = do
  inp <- readFile "input.txt"
  part1result <- part1 <$> pure inp
  part2result <- part2 <$> pure inp
  putStrLn $ "part 1: " ++ (show part1result)
  putStrLn $ "part 2: " ++ (show part2result)

part1 :: String -> Int
part1 = foldr (\x -> if x == '(' then succ else pred) 0 . init

part2 :: String -> Int
part2 = fromJust . findIndex (==(-1)) . scanl (\x y -> (if y == '(' then succ else pred) x) 0 . init
