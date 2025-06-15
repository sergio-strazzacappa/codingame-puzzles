def to_decimal(decimary):
    decimal = 0
    pos = len(decimary) - 1

    for d in decimary:
        if d == 'A':
            d = 10
        decimal += int(d) * 10 ** pos
        pos -= 1

    return decimal

def to_decimary(decimal):
    decimal = str(decimal)[::-1]
    decimary = []
    carry = False
    skip = False

    for d in decimal:
        if skip:
            continue
        skip = False
        d = int(d)
        if carry:
            decimary.insert(0, 'A')
            if d == 0:
                d = 9
                skip = True
            else:
                d -= 1
            carry = False
        if d > 0:
           decimary.insert(0, str(d))
        else:
            carry = True

    return decimary

count = int(input())
addition = 0

for decimary in input().split():
    addition += to_decimal(decimary)

print(''.join(to_decimary(addition)))
