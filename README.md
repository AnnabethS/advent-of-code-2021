# Anna's Advent of Code 2021

maybe this year i will actually complete it

## Daily Log

### Day 1

- Fairly easy puzzle today, a nice intro

### Day 2

- Slightly more challenging today
- Had some memory management troubles today

### Day 3

- Screwed up some memory management again today, not the easiest fix

### Day 4

- I had massive memory management issues again today, lots of strange
behaviours, in the end the final bug was missing a blindingly obvious logical
oversight

### Day 5

- No memory management issues today :)
- A fairly nice puzzle, made some structs for an easier time, helped a lot

### Day 6

- Used a nice linked list implementation for part 1,
- linked list iteration did not scale well to part 2, so i implemented a
smarter strategy for part 2

### Day 7

- Got a little stuck with the 2nd part today, but was right about mean
being correct, turns out to +/- 0.5, so i needed to check and input both

### Day 8

- part 1 was very easy
- part 2 took me ages, working out the logic and then i had quite a few bugs
suprisingly though, none were memory management related
- this is the first day that im not finishing on the day of its release

### Day 9

- not too bad today, part 1 was very easy
- i spent ages overengineering a solution for part 2 that ended up not working.
- another linked list implementation

### Day 10

- fairly easy today, wrote a nice stack based implementation that worked for
both parts, with only minor tweaks for part 2
- spent a while on part 2 fixing an overflow, due to the values overflowing
an int

### Day 11

- easiest day for a while, the diff between part 1 and 2 is like a few lines
almost overengineered a solution with a queue of flashed octopi but the puzzle
input is only 10*10 so its really unessecary.

### Day 12
- medium difficulty today, took a while to get going
- used a linked list for the working and finished paths, and then inside them a fixed
length string which i just made large enough to always hold the maximum path length
- had issues with time to completion on the second one, forgot i put the while loop in
that traverses the entire linked list for debugging purposes. i had removed the printf
but left the loop in, and after that it completed in about 2s
