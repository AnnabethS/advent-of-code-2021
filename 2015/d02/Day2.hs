module Day2 where
import Data.List

newtype Present = Present [Int] deriving (Show, Eq)

main :: IO()
main = do
  inp <- readFile "input.txt"
  strs <- lines <$> pure (init inp)
  presents <- f <$> pure strs
  part1Result <- part1 <$> pure presents
  part2Result <- part2 <$> pure presents
  putStrLn $ "part 1:" ++ (show part1Result)
  putStrLn $ "part 2:" ++ (show part2Result)

  where
    f :: [String] -> [Present]
    f = map strToPresent
  
{-
# parsing
-}

strToPresent :: String -> Present
strToPresent = Present . map read . splitOn 'x'

splitOn :: (Eq a) => a -> [a] -> [[a]]
splitOn _ [] = []
splitOn x ys | x `elem` ys = (\(a,b) -> a : (splitOn x (tail b))) $ break (==x) ys
             | otherwise = [ys]

{-
# individual present handling
-}

part1 :: [Present] -> Int
part1 = sum . map getSqFeet
  where
    getSqFeet :: Present -> Int
    getSqFeet p = let pa = areas p in (sum $ map (*2) pa) + minimum pa
    areas :: Present -> [Int]
    areas (Present [x,y,z]) = [x*y, x*z, y*z]
    areas _ = error "bad args passed to areas"

part2 :: [Present] -> Int
part2 = sum . map getRibbon
  where
    getRibbon :: Present -> Int
    getRibbon p@(Present xs) = (product xs) + (minimum $ perims p)
    perims :: Present -> [Int]
    perims (Present [x,y,z]) = [2*x + 2*y, 2*x + 2*z, 2*y + 2*z]
