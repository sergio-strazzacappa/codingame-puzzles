stream = input()
threshold = int(input())
cards = ["A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"] * 4

for word in stream.split('.'):
    valid = True
    to_remove = []
    for i in word:
        if i in cards:
            to_remove.append(i)
        else:
            valid = False
    if valid:
        for i in to_remove:
            cards.remove(i)

less = 0
value = -1

for i in cards:
    if i == 'A':
        value = 1
    elif i >= '2' and i <= '9':
        value = int(i)
    elif i == 'T' or i == 'J' or i == 'Q' or i == 'K':
        value = 10
    if value < threshold:
        less += 1

print(f"{round(less / len(cards) * 100)}%")
