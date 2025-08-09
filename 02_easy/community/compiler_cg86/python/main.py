expression = input().split(' ')

values = []
sign = '+'

for e in expression:
    if e == '+' or e == '-':
        sign = e
    else:
        values.append(int(sign + e))

while len(values) > 0:
    current = values[0]
    del values[0]
    count = values.count(current) + 1

    tmp = values[:]

    for v in tmp:
        if current == v:
            values.remove(current)

    if count > 1:
        print("REPEAT", count)
    if current >= 0:
        print("ADD cgx", current)
    else:
        print("SUB cgx", -current)

print("EXIT")
