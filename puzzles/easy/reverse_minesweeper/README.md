# Reverse Minesweeper

## Goal

Given a grid of mine locations (where **.** are empty cells and **x** are
mines), your goal is to display the grid like it appears if you win the game.

Each position is a digit indicating the number of mines bordering it (including
diagonals). The mines (**x**) don't appear anymore. Mines and positions that do
not border any mines both appear as empty cells (**.**).

## Input

-   Line 1: an integer **w** for the width of the grid
-   Line 2: an integer **h** for the height of the grid
-   Next **h** lines: each line of the minefield, with dots (**.**) or mines
    (**x**)

## Output

-   **h** lines of width **w** showing the completed game of _Minesweeper_

## Constraints

-   1 &leq; **w** &leq; 30
-   1 &leq; **h** &leq; 30
