# Sand Fall

## Goal

**n** grains of sand are being dropped one at a time inside a box of dimensions
**w** x **h**. Display the resulting box content after the last grain stopped
falling.

Each grain of sand is represented by an alphabetical character (**a-z** or
**A-Z**) and by its initial position **p** above the box.

## Sand behaivor

-   If there is an empty space below it, it drops down
-   If there is not an empty space directly below it, but there is space at
    either **diagonally adjacent** position below (left or right, see the next
    two rules), then it will move horizontally in that direction before falling
    down again
-   If it is a **lowercase** character, it first tries to fall **down**, then
    towards the **right**, and then towards the **left**
-   If it is an **uppercase** character, it first tries to fall **down**, then
    towards the **left**, and then towards the **right**
-   If it can't fall down (below, to the right, or to the left) it has reached
    its final position

### Example

With this input:

<pre style="color:#FFFFFF">
5 3
6
a 2
b 2
c 2
d 2
e 2
F 2
</pre>

After **a 2**, _a_ drops to the bottom. (_x_ are only here for explanation
purposes).

<pre style="color:#FFFFFF">
xxxxx
xxxxx
xxaxx
</pre>

After **b 2**, _b_ couldn't go on _a_, so it tried right of _a_ (because _b_ is
lowercase) and found empty space.

<pre style="color:#FFFFFF">
xxxxx
xxxxx
xxabx
</pre>

After **c 2**, _c_ couldn't go on _a_, tried right but couldn't go on _b_, so
it tried left and found empty space.

<pre style="color:#FFFFFF">
xxxxx
xxxxx
xcabx
</pre>

After **d 2**, _d_ couldn't go on _a_, tried right but couldn't go on _b_, tried
left but couldn't go on _c_, so reached its final position.

<pre style="color:#FFFFFF">
xxxxx
xxdxx
xcabx
</pre>

After **e 2**, _e_ couldn't go on _d_, found empty space right of _d_, kept
falling, couldn't go on _b_, found empty space right of _b_.

<pre style="color:#FFFFFF">
xxxxx
xxdxx
xcabe
</pre>

After **F 2**, _F_ couldn't go on _d_, found empty space left of _d_, kept
falling, couldn't go on _c_, found empty space left of _c_.

<pre style="color:#FFFFFF">
xxxxx
xxdxx
Fcabe
</pre>

## Input

-   Line 1: Two integers **w** and **h** representing the width and height of
    the box
-   Line 2: **n** the number of grains of sand being dropped
-   Next **n** lines: The character **s** representing the grain of sand
    followed by its initial position **p** above the box, separated by a space.
    **p** = 0 if it is above the left-most column and **p** = **w** - 1 if it is
    above the right-most column of the box

## Output

-   **h** lines: the box content, outlined by **|** on both sides
-   Last line: the box bottom, represented by **+----+** where **-** is repeated
    **w** times

## Constraints

-   2 &leq; **w**, **h** &leq; 50
-   0 &lt; **n** &lt; 256
-   0 &leq; **p** &lt; **w**
-   All grains will fit inside the box
