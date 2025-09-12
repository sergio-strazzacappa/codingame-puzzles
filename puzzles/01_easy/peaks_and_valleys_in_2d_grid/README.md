# Peaks And Valleys in 2D Grid

## Goal

Given a grid of integers, where each integer represents the height of a cell,
find all peaks (cells higher than all neighbors) and valleys (cells lower than
all neighbors). Neighbors include orthogonally and diagonally adjacent cells.

The output is 2 lines:

-   Peaks coordinates **(x, y)** separated by a comma and a space, or **NONE**
    if none
-   Valleys coordinates **(x, y)** separated by a comma and a space, or **NONE**
    if none

Coordinates use (column, row) indexing and are printed in reading order (top to
bottom, left to right).

_Note: The top-left corner is (0, 0)_

## Input

-   Line 1: The number of lines in the grid - **h**
-   Next **h** lines: A line of the grid

## Output

-   Line 1: The coordinates for peaks or **NONE**
-   Line 2: The coordinates for valleys or **NONE**

## Constraints

-   3 &leq; **h**, the width of the grid &leq; 10
-   10000 &leq; The integers in the grid &leq; 10000
