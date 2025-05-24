# Rock Paper Scissors Lizard Spock

## Goal

An international **Rock Paper Scissors Lizard Spock** tournament is organized,
all players receive a number when they register.

Each player chooses a sign that he will keep throughout the tournament among:

-   Rock (R)
-   Paper (P)
-   sCissors (C)
-   Lizard (L)
-   Spock (S)

1.  **Scissors** cuts **Paper**
2.  **Paper** covers **Rock**
3.  **Rock** crushes **Lizard**
4.  **Lizard** poisons **Spock**
5.  **Spock** smashes **Scissors**
6.  **Scissors** decapitates **Lizard**
7.  **Lizard** eats **Paper**
8.  **Paper** disproves **Spock**
9.  **Spock** vaporizes **Rock**
10. **Rock** crushes **Scissors**

and in case of a tie, the player with the lowest number wins (it's scandalous
but it's the rule).

## Example

<pre style="color:#FFFFFF">
4 R \
      1 P \
1 P /      \
             1 P
8 P \      /     \
      8 P /       \
3 R /              \
                     2 L
7 C \              /
      5 S \       /
5 S /      \     /
             2 L
6 L \      /
      2 L /
2 L /
</pre>

The winner of the tournament is player 2. Before winning, he faced player 6,
then player 5 and finally player 1.

## Input

-   Line 1: an integer **N** representing the number of participants in the
    competition
-   Lines 2 to **N**+1: an integer **NUMPLAYER** indicating the player number
    (players have distinct numbers between 1 and **N**) followed by a letter
    **R**, **P**, **C**, **L** or **S** indicating the chosen sign
    **SIGNPLAYER**

## Output

-   Line 1: the number of the winner
-   Line 2: the list of its opponents separated by spaces

## Constraints

-   **N** is a 2^k value (2, 4, 8, 16, ..., 1024)
-   2 &leq; **N** &leq; 1024
