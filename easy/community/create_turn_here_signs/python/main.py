direction, *rest = input().split()
quantity, height, thickness, space, indent = map(int, rest)

def print_arrow(symbol):
    for j in range(quantity):
        print(symbol * thickness, end='')
        if j < quantity - 1:
            print(" " * space, end='')
    print()


if direction == "right":
    for i in range(height):
        if i <= height // 2:
            print(" " * indent * i, end='')
        else:
            print(" " * indent * (height - i - 1), end='')
        print_arrow('>')
elif direction == "left":
    for i in range(height):
        if i <= height // 2:
            print(" " * indent * (height // 2 - i), end='')
        else:
            print(" " * indent * (i - height // 2), end='')
        print_arrow('<')
