size = int(input())
scores = []

number_players = int(input())
for _ in range(number_players):
    name = input()
    scores.append([name, 0])

number_throws = int(input())
for _ in range(number_throws):
    name, x, y = input().split()
    x = int(x)
    y = int(y)

    if abs(x) + abs(y) <= size / 2:
        # inside the diamond
        points = 15
    elif (x ** 2 + y ** 2) ** 0.5 <= size / 2:
        # inside the circle
        points = 10
    elif x >= -(size / 2) and x <= size / 2 and y >= -(size / 2) and y <= size / 2:
        # inside the square
        points = 5
    else:
        points = 0

    for elem in scores:
        if elem[0] == name:
            elem[1] += points

scores.sort(key=lambda x: x[1], reverse=True)

for score in scores:
    print(score[0], score[1])
