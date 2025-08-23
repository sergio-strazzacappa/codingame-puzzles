# The Broken Editor

## Goal

Your favourite code editor broke, it can't display what you're typing anymore!  
Replace the part that handles the keyboard inputs and build the output yourself!

All **typed_keys** can be either a **character**, a **keyboard arrow**
(left / right) represented by &lt; and &gt; or a **backspace** represented by
the minus sign **-**

-   &lt; moves the editor's cursor to the left
-   &gt; moves the editor's cursor to the right
-   \- removes one character on the left side of the cursor's position
    (backspace behaviour)

Keep in mind that a cursor has boundaries: from the left of the first character
to the right of the last one.

### Example 1

You typed an extra **L** in **Helllo World** and removed it with a backspace:

-   **Input**: Helll-o World
-   **Output**: Hello World

### Example 2

While typing too fast, you skipped the **e**. You pressed left arrow twice,
typed **e** then went back to the right and typed the rest ("o World"):

-   **Input**: Hll&lt;&lt;e&gt;&gt;o World
-   **Output**: Hello World

Good luck!

## Input

-   Line 1: **typed_keys** A string representing all the pressed keys
    (characters/arrows/backspaces)

## Output

-   Line 1: The text to display in the editor's window

## Constraints

-   1 &leq; length of **typed_keys** &leq; 80
