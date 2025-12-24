from Point import Point

def distance(p:Point, q:Point):
    return round((
        (p.get_x() - q.get_x()) ** 2 +
        (p.get_y() - q.get_y()) ** 2 +
        (p.get_z() - q.get_z()) ** 2) ** 0.5)


length  = int(input())
width   = int(input())
depth   = int(input())
n       = int(input())

map = []

for z in range(depth):
    for y in range(width):
        for x in range(length):
            map.append(Point(x, y, z))

x = 0
y = 0
z = 0

for i in range(n):
    s = input()

    if s == '':
        y = 0
        z += 1
        continue

    x = 0
    for cell in s:
        if cell != '.':
            if cell <= '9':
                radius = int(cell)
            else:
                radius = ord(cell) - ord('A') + 10

            p = Point(x, y, z, radius)

            for m in map:
                brightness = radius - distance(m, p)

                if brightness < 0:
                    brightness = 0
                if brightness > 35:
                    brightness = 35
            
                m.add_brightness(brightness)
        x += 1
    
    y += 1

for cell in map:
    brightness = cell.get_brightness()

    if brightness <= 9:
        brightness = str(brightness)
    else:
        brightness = chr(ord('A') + brightness - 10)

    print(brightness, end="")

    if cell.get_x() == length - 1:
        print()

        if cell.get_y() == width - 1 and cell.get_z() < depth - 1:
            print()
