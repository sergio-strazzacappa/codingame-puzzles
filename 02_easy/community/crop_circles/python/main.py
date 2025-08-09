import math

instructions = input().split()

field = [["{}" for x in range(19)] for y in range(25)]

action = 0
for i in instructions:
    action = 0
    if i.startswith("PLANTMOW"):
        action = 1
        i = i.removeprefix("PLANTMOW")
    elif i.startswith("PLANT"):
        action = 2
        i = i.removeprefix("PLANT")

    x, y, *d = i
    x = ord(x) - ord('a')
    y = ord(y) - ord('a')
    d = int(''.join(d))

    for yy in range(25):
        for xx in range(19):
            dist = math.dist([x, y], [xx, yy])

            if dist <= d / 2:
                if action == 0:
                    field[yy][xx] = "  "
                elif action == 1:
                    if field[yy][xx] == "{}":
                        field[yy][xx] = "  "
                    else:
                        field[yy][xx] = "{}"
                elif action == 2:
                    field[yy][xx] = "{}"

for y in field:
    for x in y:
        print(x, end='')
    print()
