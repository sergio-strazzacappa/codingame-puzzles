cols, rows, t1, t2, t3 = [int(i) for i in input().split()]

first_picture = []
second_picture = []
ASTEROIDS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
asteroids = [] # x, y, letter, dx, dy

# Read both pictures of the sky
for y in range(rows):
    first_picture_row, second_picture_row = input().split()
    first_picture.append(first_picture_row)
    second_picture.append(second_picture_row)

# Identify the asteroids in the first picture
for y in range(rows):
    for x in range(cols):
        if first_picture[y][x] in ASTEROIDS:
            asteroids.append([x, y, first_picture[y][x], 0, 0])

# Sort the asteroids by letter
asteroids = sorted(asteroids, key=lambda x: x[2], reverse=True)

# Calculate the movement of each asteroid
for y in range(rows):
    for x in range(cols):
        if second_picture[y][x] not in ASTEROIDS:
            continue
        for a in asteroids:
            if a[2] == second_picture[y][x]:
                a[3] = (x - a[0]) / (t2 - t1)
                a[4] = (y - a[1]) / (t2 - t1)
                a[0] = x
                a[1] = y

# Build the third picture
third_picture = []

for y in range(rows):
    row = []
    for x in range(cols):
        row .append('.')
    third_picture.append(row)

for i in asteroids:
    x = i[0] + i[3] * (t3 - t2)
    y = i[1] + i[4] * (t3 - t2)

    if x < 0:
        continue
    if x > cols - 1:
        continue
    if y < 0:
        continue
    if y > rows - 1:
        continue

    third_picture[int(y)][int(x)] = i[2]

# Print the solution
for y in range(rows):
    for x in range(cols):
        print(third_picture[y][x], end="")
    print()
