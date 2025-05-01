# Should Bakers Be Frugal?

## Goal

### Background Terms

-   A biscuit is round (a circle)
-   Measurements are in inches (not necessarily full inches)
-   When a Baker has a flattened-out square of dough (_DoughSquare_), he will
    cut-out biscuits (in grid-style orderly columns and rows) until no more
    biscuits can be cut-out

### The Difference

There are two types of Bakers: _Wasteful_ and _Frugal_:

-   A **Wasteful Baker** will stop there, and throw away the remaining dough
-   A **Frugal Baker** will take the remaining dough and re-form it into another
    (smaller) DoughSquare, and repeat the cutting process. He will continue to
    do this until no full-biscuit can be cut-out

_NOTE: At the end, there might be enough dough left to manually shape into a
circle of the required diameter, but the Baker is not allowed to do this. In
order to make a biscuit, the DoughSquare itself must be big enough so that the
Baker can place the biscuit cutter fully on it._

### The Question

Given the length of a **side** of the starting DoughSquare, and the **diameter**
of the biscuit cutter, how many **more** biscuits can a _Frugal Baker_ cut-out
than a _Wasteful Baker_?

## Input

-   Line 1: Two floats **side** and **diameter** separated by a space

## Output

-   Line 1: How many **more** biscuits a _Frugal Baker_ makes than a
    _Wasteful Baker_

## Constraints

-   0 &lt; **diameter** &lt; **side** &lt; 100
