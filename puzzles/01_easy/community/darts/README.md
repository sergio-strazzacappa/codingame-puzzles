# Darts

## Goal

A group of your friends want to have a dart throwing competition with a unique
target. They've asked you, their tech savvy friend, to automate the scoring as
they often squabble over scoring, and have trouble keeping track of who's turn
it is to throw.

The target is a square. The square has a circle inscribed within whose diameter
matches the width of the square. The circle, in turn, encompasses a diamond
whose width from corner to corner matches the circle's diameter. The diamond can
be thought of as a square rotated by 1/4 PI so that the corners of the square
are on the x and y axes.

Darts landing within the square but not within the circle or diamond are worth 5
points. Darts landing within the circle but not within the diamond are worth 10
points. Darts landing within the diamond are worth 15 points.

In the event of a tie, competitors should be ordered as they were in the name
list, so competitors appearing earlier in the name list are listed earlier in
ties.

_Note: Darts landing on the edge of a shape are considered within the shape._

_Note: The center of the square, circle and diamond is at (0,0)._

## Input

-   Line 1: **SIZE** (length of a side) of square as integer
-   Line 2: The number of competitors in name list, **N**
-   Next **N** lines: name of a single competitor in name list
-   Next line: Number of throws, **T**
-   Next **T** lines: Name of competitor, integer x-coordinate and integer
    y-coordinate of throw, each separated by a space, **name** **X** **Y**

## Output

-   **N** lines: Competitor's name, a space, and that competitor's score, in
    descending order by score, and in order of appearance in the input list in
    case of a tie

## Constraints

-   10 &leq; **SIZE** &leq; 100
-   1 &leq; **N** &leq; 10
-   1 &leq; **T** &leq; 50
-   -300 &leq; **X** &leq; 300
-   -300 &leq; **Y** &leq; 300
