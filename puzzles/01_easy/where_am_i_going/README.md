# Where Am I Going?

## Goal

Your program must describe the path through a field.

The start is always from outside the field at the top left, heading right.

The output will be the number of steps to move. \
Followed by **R** to turn right or **L** to turn left if the path has not yet
ended. \
This is repeated until the path ends. The path may end in the middle of the
field or at the edge.

_Note: the path will be such that there is only one solution._

## Input

-   Line 1: An integer **h** for the number of lines
-   Line 2: An integer **w** for the length of each line
-   Next **h** lines: A string of length **w**. **#** for the path and **.** for
    the field that is not the path

## Output

-   Line 1: A string for the path

## Constraints

-   1 &leq; **h** &leq; 30
-   3 &leq; **w** &leq; 30
