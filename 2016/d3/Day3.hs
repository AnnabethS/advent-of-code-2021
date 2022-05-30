module Day3 where
import Data.List

main :: IO ()
main = do
  inp <- readFile "input.txt"
  ls <- lines <$> pure inp
  triangles <- parse <$> pure ls
  part1result <- (length . filter isRealTriangle) <$> pure triangles
  part2result <- (length . filter isRealTriangle . part2transform) <$> pure triangles
  putStrLn ("part1: " ++ show part1result)
  putStrLn ("part2: " ++ show part2result)


parse :: [String] -> [[Int]]
parse = map (map read . words)

part2transform :: [[Int]] -> [[Int]]
part2transform [] = []
part2transform xs = (transpose $ take 3 xs) ++ (part2transform $ drop 3 xs)

isRealTriangle :: [Int] -> Bool
isRealTriangle = all p . permutations
  where
    p [x,y,z] = z < (x+y)
    p x = error $ "list of >3 passed to p: " ++ (show x)
