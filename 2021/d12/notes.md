# Day 12 Notes

## Part 1

- For the current symbol, append to the linked list each possibility from it
- prevent going back to small caves in it
- infinite loops arent possible since big caves always connect through small
ones, therefore the paths should be finite
- store the path as a char array of size (maxlines*3)+1 since thats the max
size a path could be if there was only 1.
- remove current linked list symbol and free it, move to next list head.
- keep a second linked list of finished paths, append to that when an end
is selected.
