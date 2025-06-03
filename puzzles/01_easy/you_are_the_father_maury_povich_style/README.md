# You Are The Father: Maury Povich Style

## Goal

### ~ ~ ~ Pop Culture Background ~ ~ ~

Maury Povich hosted a popular talk show in America for decades.

A famous and common theme for an episode was helping a new mom figure out which
of her past _gentleman callers_ is her child's biological father. Maury’s staff
would swab and paternity-test a sample from each possible man and then Maury
would announce with much fanfare either _You are NOT the father!_ or _You ARE
the father!_

(For your amusement only, see banner image and video link far below for clips of
that; it isn't needed to solve this puzzle.)

### ~ ~ ~ Biology Background ~ ~ ~

Every creature has multiple _Pairs of Chromosomes_, henceforth called
**chromPair**s.

For each **chromPair**, Mother and Father each contribute 1 chromosome to form
the child's **chromPair**.

In the very simplified world of this puzzle, a chromosome is simply 1 character
and a **chromPair** is simply 2 characters.

### ~ ~ ~ Example ~ ~ ~

The species has 2 **chromPair**s. \
Mother is: **ab** **cd** \
Father is: **wx** **yz**

Their child is created by having:

-   1 of **ab** plus 1 of **wx** for its 1st **chromPair**
-   1 of **cd** plus 1 of **yz** for its 2nd **chromPair**

So the child could be: **aw cy** or **bw cz** ... or any of 14 other combinations.

However, their child cannot be:

-   **aq cy** ... because **q** is not a chromosome from either parent
-   **ab cy** ... because it doesn't have anything from Father's 1st **chromPair**
-   **az cy** ... because even though Father has **z**, it's not in his 1st **chromPair**

**NOTE**: Order in **chromPair** doesn't matter: **aw** is exactly equal to
**wa**.

### ~ ~ ~ Your Task ~ ~ ~

Given the above rules, help Maury Povich tell each single **mother** who the
**actualFather** of her child is.

_For your amusement, see the inspiration for this puzzle:
https://www.youtube.com/watch?v=br4kx6yrPzo_

_Reportedly, Maury Povich was especially proud of cases where men would own up
to their paternity, get involved in their child's life, and reunite with the
mother to form a stable nuclear family. Much of his focus on paternity tests
came from his steadfast belief in the virtues of the nuclear family and his
stance that children were best served with both parents involved in the child'
life._

_Source: https://en.wikipedia.org/wiki/Maury\_(talk\_show)_

## Input

-   Line 1: **Mother** **mother**'s name: some spaces, followed by some number
    of **chromPair**s (each separated by a space)
-   Line 2: **Child** **child**'s name: some spaces, followed by some number of
    **chromPair**s (each separated by a space)
-   Line 3: An integer, the number of possible fathers (**numOfPossibleFathers**)
-   Next **numOfPossibleFathers** Lines: **Possible father**'s name: some
    spaces, followed by some number of **chromPair**s (each separated by a
    space)

## Output

-   Line 1: **actualFather**, you are the father!

## Constraints

-   All names are one word (no spaces)
-   All creatures in a given test/validator have the same number of
    **chromPair**s
-   There is only one that can be the father; in other words, there is always
    exactly one **actualFather**
