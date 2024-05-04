# The descent

## The goal

Destroy the mountains before your starship collides with one of them. For that, shoot the highest mountain on your path.

## Rules

**At the start of each game turn**, you are given the height of the 8 mountains from left to right.

**By the end of the game turn**, you must fire on the highest mountain by outputting its index (from 0 to 7).

Firing on a mountain will only destroy part of it, reducing its height. Your ship descends after each pass.

<div class="victory-conditions">
    <div class="win">
        <h3 class="title">Victory conditions</h3>
        <p class="content">You win if you destroy every mountain</p>
    </div>
        <div class="lose">
        <h3 class="title">Lose conditions</h3>
        <p class="content">
            <ul>
                <li>Your ship crashes into a mountain</li>
                <li>You provide incorrect output or your program times out</li>
            </ul>
        </p>
    </div>
</div>

## Note

Don’t forget to run the tests by launching them from the _Test cases_ window. The tests provided and the validators used to calculate your score are slightly different to avoid hard-coded solutions.

## Game input

Within an infinite loop, read the heights of the mountains from the standard input and print to the standard output the index of the mountain to shoot.

## Input for one game turn

8 lines: one integer **mountainH** per line. Each represents the height of one mountain given in the order of their index (from 0 to 7).

## Output for one game turn

A **single line** with one integer for the index of which mountain to shoot.

## Constraints

- 0 ≤ **mountainH** ≤ 9
- Response time per turn ≤ 100ms

<style>
    .victory-conditions {
    }

    .win {
        background-color: #203634;
    }

    .lose {
        background-color: #631d27;
    }

    .title {
        padding: 10px;
    }

    .content {
        padding-left: 20px;
        margin-bottom: 10px;
    }
</style>
