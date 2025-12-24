rows = int(input())
cols = int(input())

lights = []

for y in range(rows):
    s = input()
    for x in range(len(s)):
        if s[x] != '.':
            if s[x].isdigit():
                lights.append((int(s[x]), x, y))
            else:
                lights.append((ord(s[x]) - ord('A') + 10, x, y))

city = [['0' for x in range(cols)] for y in range(rows)]

for y in range(rows):
    for x in range(cols):
        brightness = 0
        for light in lights:
            distance = round(((x - light[1]) ** 2 + ((y - light[2])) ** 2) ** 0.5)

            if light[0] - distance > 0:
                brightness += light[0] - distance
        if (brightness < 0):
            brightness = 0
        if (brightness > 35):
            brightness = 35

        if brightness > 9:
            city[y][x] = chr(brightness - 10 + ord('A'))
        else:
            city[y][x] = str(brightness)

for y in city:
    for x in y:
        print(x, end='')
    print()
