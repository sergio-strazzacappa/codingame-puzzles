# Dice Probability Calculator

## Goal

Each Friday, you play the famous _Fix your Dungeon_ RPG with friends. You'd like
to optimize your character: you need to know the probability of success of each
test involving dice throws.

Your program takes in input an expression (possibly with dice throws) and must
print all possible outcomes along with their probabilities.

The expression is an arithmetic expression **with parentheses** and the
following operators, from highest to lowest precedence:

-   **\*** multiplication
-   **+** and **-** addition and subtraction
-   &gt; greater-than comparison: evaluates to 1 if true, 0 if false

The operands are one of:

-   **n**: a decimal positive integer
-   **dn**: a _d_ followed by a strict positive number, representing a die throw
    from 1 to **n** by a uniform distribution

Examples of expressions:

-   **3\*2+5** evaluates to 11
-   **d6**: evaluates to an integer from 1 to 6, uniform
-   **d6+d6**: represents a double-dice throw
-   5&gt;2: evaluates to 1

## Input

-   A unique line containing the input expression. The expression contains no
    spaces

## Output

-   **N** lines: an integer (outcome), a space and a float (percent probability
    of this outcome)
-   Outcomes are sorted in ascending order
-   Floats are formatted with 2 decimal figures, rounded

## Constraints

-   The inputs are all valid expressions: no error handling is needed
-   Maximum length of expression: **100** chars
