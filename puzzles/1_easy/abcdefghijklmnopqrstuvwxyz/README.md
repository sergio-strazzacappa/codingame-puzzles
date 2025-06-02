# abcdefghijklmnopqrstuvwxyz

## Goal

This program problem find out the consecutive string from **a** to **z** in
alphabetical order in a multi-line **string** **m** of **n** lines of length
**n**.

You can move **up**, **right**, **left** or **down**. First, you find the **a**.
If there is a **b** either **up**, **down**, **left** or **right** from the
position of **a**, you can move there. If there is a **c** either **up**,
**down**, **left** or **right** from the position of **b**, you can move there.
Continues below to **z**.

Rewrites all nonconsecutive strings of letters **a** through **z** to **-**.
In other words, this problem only displays the consecutive string from **a** to
**z** in a multi-line string **m** of **n** lines of length **n**.

Answer to output, as follows.

### Example:

<pre style="color:#FFFFFF">
10
qadnhwbnyw
iiopcygydk
bahlfiojdc
cfijtdmkgf
dzhkliplzg
efgrmpqryx
loehnovstw
jrsacymeuv
fpnocpdkrs
jlmsvwvuih
</pre>

The answer to this is...

<pre style="color:#FFFFFF">
----------
----------
ba--------
c-ij------
d-hkl---z-
efg-mpqryx
----no-stw
--------uv
----------
----------
</pre>

As above, only the string alphabetically from **a** to **z** should be
displayed, and the other parts should be **-**.

## Input

-   Line 1: An integer **n** for the size of the string figure
-   Next **n** Lines: multi-line string **m**

## Output

-   Output only strings alphabetically from **a** to **z** should be displayed
    in multi-line string **m**, and the other parts should be **-**

## Constraints

-   10 &leq; **n** &leq; 30
-   **m** consists only of lowercase alphabetical characters
-   There may be more than one **a**
-   There is only one **abcdefghijklmnopqrstuvwxyz** in the string figure
