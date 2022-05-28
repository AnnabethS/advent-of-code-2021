module Day1 where

data Instruction = L Int | R Int deriving Show
data Dir = North | East | South | West deriving (Show, Eq, Enum)
type Pos = (Dir, (Int, Int))

main :: IO()
main = do
  inp <- readFile "input.txt"
  inp <- words <$> pure inp
  instructions <- parse <$> pure inp
  part1result <- part1 <$> pure instructions
  part2result <- part2 <$> pure instructions
  putStrLn $ "part 1: " ++ (show part1result)
  putStrLn $ "part 2: " ++ (show part2result)

parse :: [String] -> [Instruction]
parse = map go
  where go ('R':num) = R (read (if (last num) == ',' then init num else num))
        go ('L':num) = L (read (if (last num) == ',' then init num else num))
        go s = error $ "bad data in parse: " ++ s

part1 :: [Instruction] -> Int
part1 = (\(_, (x,y)) -> (abs x) + (abs y)) . foldl go (North, (0,0))
  where
    go :: Pos -> Instruction -> Pos
    go pos inst = move (turn pos inst) inst

move :: Pos -> Instruction -> Pos
move (North, (x,y)) z = (North, (x,y+(fromInstruction z)))
move (South, (x,y)) z = (South, (x,y-(fromInstruction z)))
move (East, (x,y)) z = (East, (x+(fromInstruction z), y))
move (West, (x,y)) z = (West, (x-(fromInstruction z), y))

fromInstruction :: Instruction -> Int
fromInstruction (L a) = a
fromInstruction (R a) = a

turn :: Pos -> Instruction -> Pos
turn (facing, coords) (L _) = (turnL facing, coords)
turn (facing, coords) (R _) = (turnR facing, coords)

turnL :: Dir -> Dir
turnL North = West
turnL x = pred x

turnR :: Dir -> Dir
turnR West = North
turnR x = succ x


part2 :: [Instruction] -> Int
part2 = (\(x,y) -> (abs x) + (abs y)) . findFirstRepeated . allVisited . map snd . scanl go (North, (0,0))
  where
    go :: Pos -> Instruction -> Pos
    go pos inst = move (turn pos inst) inst

allVisited :: [(Int, Int)] -> [(Int, Int)]
allVisited xs = (concat $ map (tail . getTilesBetween) $ zip xs (tail xs)) ++ [last xs]

findFirstRepeated :: Eq a => [a] -> a
findFirstRepeated = go []
  where go fnd (x:xs) | x `elem` fnd = x
                      | otherwise = go (x:fnd) xs


getTilesBetween :: ((Int, Int), (Int, Int)) -> [(Int, Int)]
getTilesBetween ((x1,y1), (x2,y2)) | x1==x2 = [(x1, y) | y <- f y1 y2] 
                                   | y1==y2 = [(x, y1) | x <- f x1 x2]
                                   | otherwise = error "unreachable"
  where f from to | from <= to = [from..to]
                  | otherwise = reverse [to..from]
