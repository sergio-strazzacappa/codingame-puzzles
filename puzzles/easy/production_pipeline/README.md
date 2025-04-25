# Production Pipeline

## Goal

There are **N** different sequential processes in a production pipeline which
must be executed, identified by a number from 1 to **N**, and **K** constraints
given in the form _[process1] &lt; [process2]_, which means that the first
provided process must run before the second provided process.

Find a valid processing order for all processes that respects the constraints.
If none exists, output **INVALID**. Otherwise output the processes in their
order, separated by spaces. In case the order of two processes doesn't matter,
use the smaller process first.

## Input

-   Line 1: An integer **N** for the number of processes
-   Line 2: An integer **K** for the number of contraints
-   Next **K** lines: A constraint string consisting of two process numbers
    **p1** and **p2**, separated by &lt;

## Output

-   Line 1: The space-separated list of processes in processing order, or the
    text **INVALID**

## Constraints

-   0 &lt; **N** &leq; 250
-   0 &leq; **K** &leq; 250
-   1 &leq; **p1**, **p2** &leq; **N**
-   The same process number can appear in multiple constraints
