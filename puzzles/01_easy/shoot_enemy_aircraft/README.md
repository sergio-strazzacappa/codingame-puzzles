# Shoot Enemy Aircraft

## Goal

There are enemy aircraft (**&gt;** or **&lt;**) in the sky (made of **.**). Each
turn they move one cell forward. You are in charge of shooting them with a
surface-to-air missile (**^**). You can only shoot vertically. Each turn your
missiles move one cell up.

**Note**: When you shoot, the missile appears at the same altitude as the
launcher. Each turn, the missile moves one cell up. The plane disappears after
being shot, so do the missiles after having shot a plane. Every plane is
shootable. There isn't any collision between planes, you have to shoot them all.

You have to print, each turn, if you **WAIT** or if you **SHOOT**. You have to
shoot all the enemy aircraft, and your stock is just enough, so don't **SHOOT**
if you can't hit an aircraft. After shooting every missile, do not print the
last **WAIT**s.

## Input

-   Line 1: the number **n** of lines
-   **n** following lines: the description of the situation

## Output

-   As many lines as necessary, made of **WAIT** or **SHOOT**, one instruction
    per line

## Constraints

-   2 &leq; **n** &leq; 10
-   The sky is made of **n** - 1 lines, the last line is the ground
-   A sky line is made of **.** if no aircraft, **&gt;** or **&lt;** for each
    aircraft
-   The ground line is made of **\_**, and **^** for the surface-to-air missile launcher
-   There is only one missile launcher, and it's always on the ground
-   The lengths of the lines are always the same, and &leq; 40
