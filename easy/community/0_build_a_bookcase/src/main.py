#!/usr/bin/env python3

height = int(input())
width = int(input())
number_of_shelves = int(input())

# Draw the top
for i in range(width):
    if i < width / 2 and (i + 1) > width / 2:
        print("^", end="")
    elif i < width / 2:
        print("/", end="")
    else:
        print("\\", end="")
print()

height -= 1

# Draw the shelves
for i in range(number_of_shelves):
    current_height = height // number_of_shelves

    if (number_of_shelves - i) <= (height % number_of_shelves):
        current_height += 1

    for j in range(current_height):
        shelf = ""
        for k in range(width - 2):
            if j < current_height - 1:
                shelf += " "
            else:
                shelf += "_"

        print(f"|{shelf}|")
