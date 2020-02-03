# RushHour

Automatic resolution of the RushHour-like games

## File format
The first line must be \[width\],\[height\]
Then on the \[height\] following lines, there should be \[width\] char to describe the map


The border are annoted with an `x`, the exit with a `z`
The main car must be annoted with an `a`, all the other must use a letter between `b` and `f`

The solver has been tested with a 8x8 grid.
It should tell you when all the possibilities have been tested if no solutions were found.
Once the solution has been found (if a solution is available) press Enter to see the step to reproduce to solve the puzzle.

Had the idea of this solver while playing [move the block](https://play.google.com/store/apps/details?id=com.bitmango.go.unblockcasual)

Now I can solve all the puzzles :D
