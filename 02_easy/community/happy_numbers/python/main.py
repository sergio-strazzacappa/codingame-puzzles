LIMIT = 1000

n = int(input())

for i in range(n):
    x = input()
    iterations = 0
    next = x

    while True:
        next = sum([int(j) ** 2 for j in str(next)])

        if next == 1:
            print(f"{x} :)")
            break
        
        iterations += 1

        if (iterations == LIMIT):
            print(f"{x} :(")
            break
