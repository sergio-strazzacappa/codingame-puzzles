# Card Counting When Easily Distracted

## Goal

In this simplified version of _Card Counting_, you are playing **Blackjack** at a casino table that uses only one standard deck of 52 cards.

Fortunately, you have an amazing memory and incredible math skills. \
Unfortunately, you are easily distracted and there's a lot going on.

Your **streamOfConsciousness** is what you observe intermingled with your thoughts. \
Each thought or observation (separated by a period **.**) might be a series of cards or something else. It is a series of cards if it consists solely of valid cards; see abbreviations used below.

With your knowledge of all the observed cards, calculate the **percentageChance** (rounded to the nearest whole number) that the value of the next card will be less than the **bustThreshold**.
(The **bustThreshold** is what would make your hand _go-bust_/lose by going over 21. It isn't anything you need to calculate; it is provided.)

**Abbreviations used, and values**:

-   **K** = King
-   **Q** = Queen
-   **J** = Jack
-   **T** = Ten

(each of the above has a value of 10)

-   **A** = Ace (has a value of 1)
-   Each number card (**2** through **9**, inclusive) has its own face value

**Examples**:

-   **JT7A44** means: a Jack, a Ten, a 7, an Ace, and two 4s
-   **JAKE** might be your buddy, but it's not a series of cards, since _E_ isn't a valid abbreviation
-   **AT&T** might be your cell-service provider, but it's not a series of cards, since _&_ isn't a valid abbreviation
-   **T1** might be a data/telecom line, but it's not a series of cards, since _1_ isn't a valid abbreviation

## Input

**Line 1**: a string **streamOfConsciousness** \
**Line 2**: an integer **bustThreshold**

## Output

**Line 1**: an integer **percentageChance**%

## Constraints

2 ≤ **bustThreshold** ≤ 10
