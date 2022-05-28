module Day4 where
import Data.Hash.MD5
import Data.List
import Data.Maybe

main :: IO()
main = putStrLn ("part1: " ++ (show part1)) >> putStrLn ("part2: " ++ (show part2))

inp :: String
inp = "ckczppom"
 
part1 :: Int
part1 = fromJust $ findIndex p [(md5s . f) x | x <- [0..]]
  where
    p :: String -> Bool
    p = (=="00000") . take 5
    f x = (Str (inp ++ show x))

  
part2 :: Int
part2 = fromJust $ findIndex p [(md5s . f) x | x <- [0..]]
  where
    p :: String -> Bool
    p = (=="000000") . take 6
    f x = (Str (inp ++ show x))
