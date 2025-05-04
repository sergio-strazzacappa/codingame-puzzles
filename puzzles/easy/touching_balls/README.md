# Touching Balls

## Goal

You are given **N** non-overlapping spheres, each centered at
(**x**,**y**,**z**) with radius **r**. In the same order as they are given,
expand the radius of each sphere until it touches any of the other spheres.

## Input

-   Line 1: The **N**umber of spheres
-   Next **N** lines: **x** **y** **z** **r** for each sphere, space separated

## Output

-   The sum of **r**^3 for all the spheres after expansion, rounded to the
    nearest integer

## Constraints

-   2 &leq; **N** &leq; 100
-   0 &leq; **x**, **y**, **z** &leq; 100
-   0 &lt; **r** &leq; 100
