# Crack The Trio Code

## Goal

There are three positive integers, called **triads**. By selecting 1 to 3 of
these numbers (with repetitions allowed) and summing them, you obtain what is
known as **triad sums**.  
You are given a sorted subset **L** of triad sums. Your task is to determine the
original triads.

-   If there is only one possible set of triads, output them in ascending order
    (comma-separated)
-   If there are multiple possible sets, output **many**
-   If no valid set exists, output **none**

## Input

-   Line 1: A comma-separated list of integers representing a sorted subset of
    triad sums (with no duplicates)

## Output

-   Line 1: The answer as specified in the statement

## Constraints

-   max(**L**) &leq; 120
