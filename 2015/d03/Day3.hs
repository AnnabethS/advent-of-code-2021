module Day3 where
import Data.List

main :: IO()
main = do
  inp <- readFile "input.txt"
  moves <- parseInputToVec . init <$> pure inp
  part1Result <- part1 <$> pure moves
  part2Result <- part2 <$> pure moves
  putStrLn $ "part1: " ++ (show part1Result)
  putStrLn $ "part2: " ++ (show part2Result)

parseInputToVec :: String -> [(Int, Int)]
parseInputToVec = map f
  where
    f '^' = (0, 1)
    f 'v' = (0, -1)
    f '<' = (-1, 0)
    f '>' = (1, 0)
    f _ = error "invalid input whilst parsing"

part1 :: [(Int, Int)] -> Int
part1 = length . nub . doMoves

tupAdd :: (Int, Int) -> (Int, Int) -> (Int, Int)
tupAdd (a,b) (c,d) = (a+c, b+d)

part2 :: [(Int, Int)] -> Int
part2 xs = length . nub $ (roboList ++ santaList)
  where
    roboList = doMoves $ getEvenElems (tail xs)
    santaList = doMoves $ getEvenElems xs

doMoves :: [(Int, Int)] -> [(Int, Int)]
doMoves = scanl tupAdd (0,0)
  
getEvenElems :: [a] -> [a]
getEvenElems (x:_:xs) = x : getEvenElems xs
getEvenElems _ = []
