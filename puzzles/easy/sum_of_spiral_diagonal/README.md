# Sum Of Spiral's Diagonal

## Goal

Given a matrix of shape **N** × **N** arranged in a _spiral_, with its numbers
spiralling from 1 to **N**^2 inward, what is the sum of its diagonals? See
examples to clarify what a spiral is.

**Example 1**:

The input: 3

Gives the following spiral:

<pre style="color:#FFFFFF">
| 1 | 2 | 3 |
| 8 | 9 | 4 |
| 7 | 6 | 5 |
</pre>

The sum of the diagonals is: 1 + 3 + 5 + 7 + 9 = 25

**Example 2**:

The input: 4

Gives the following spiral:

<pre style="color:#FFFFFF">
| 1  | 2  | 3  | 4 |
| 12 | 13 | 14 | 5 |
| 11 | 16 | 15 | 6 |
| 10 | 9  | 8  | 7 |
</pre>

The sum of the diagonals is: 1 + 4 + 7 + 10 + 13 + 14 + 15 + 16 = 80

## Input

-   **N** the number of layers of the spiral

## Output

-   **S** the sum of the diagonals

## Constraints

-   0 &lt; **N** &lt; 1500
-   0 &lt; **S** &lt; 2^32 - 1
