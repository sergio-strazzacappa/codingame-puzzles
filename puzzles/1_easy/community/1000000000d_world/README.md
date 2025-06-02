# 1000000000D World

## Goal

You are in 1000000000D World!

In 1000000000D World all vectors consist of **exactly** one billion integers.

People of 1000000000D World are quite smart and they know that due to low
entropy and _curse of dimensionality_ most of their billion-dimensional vectors
have a lot of consequent repetitions. So they always store their vectors in a
compressed form.

For example consider a vector in canonical form:

**[1 1 1 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 ... (999999995 times 3)]**

In **compressed form** it will become just:

**[3 1 2 2 999999995 3]** (which stands for 3 times 1 and 2 times 2 and
999999995 times 3)

Given two 1000000000D vectors **A** and **B** in compressed form, **find the
dot product of two vectors**.

## Dot Product Definition

For two vectors a = [a_1 a_2 ... a_n] and b = [b_1 b_2 ... b_n] dot product
**a • b** = a_1 \* b_1 + a_2 \* b_2 + ... + a_n \* b_n

## Input

-   Line 1: Compressed Vector **A**
-   Line 2: Compressed Vector **B**

## Output

-   Dot product of **A** and **B**

## Constraints

-   The absolute values of the final result and all intermediate results are
    less than 2^40
