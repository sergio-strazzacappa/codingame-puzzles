def solve(entry, index, result, solution):
    if index < len(invoices):
        result += invoices[index]
        solution.append(invoices[index])

        if entry == result:
            for i in solution:
                invoices.remove(i)
            return True
        elif result < entry:
            solved = solve(entry, index + 1, result, solution)
            if solved:
                return True

        result -= invoices[index]
        solution.remove(invoices[index])
        solve(entry, index + 1, result, solution)

n = int(input())
m = int(input())

invoices = []
letter = ord('A')

for i in range(n):
    invoices.append(int(input()))

for i in range(m):
    entry = int(input())
    solution = []
    solve(entry, 0, 0, solution),

    print(f"{chr(letter)} {entry} -", end="")
    for s in solution:
        print(f" {s}", sep="", end="")
    print()

    letter += 1
