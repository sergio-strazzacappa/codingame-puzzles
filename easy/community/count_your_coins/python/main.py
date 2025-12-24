value_to_reach = int(input())
n = int(input())

types = []
values = []

for i in input().split():
    types.append(int(i))

for i in input().split():
    values.append(int(i))

coins = 0
enough = True
while value_to_reach > 0:
    grab:int = min(values)
    index = values.index(grab)
    types[index] -= 1
    value_to_reach -= grab
    coins += 1

    if types[index] == 0:
        values.remove(grab)
        types.remove(0)

    if len(values) == 0:
        enough = False
        break

if not enough:
    coins = -1

print(coins)
