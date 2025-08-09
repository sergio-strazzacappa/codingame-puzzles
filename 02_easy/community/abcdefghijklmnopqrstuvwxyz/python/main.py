MOVES = [
    [1, 0],
    [0, 1],
    [-1, 0],
    [0, -1]
]

n = int(input())
matrix = []

def solve(current):
    letter = 'a';
    solution = []

    for y in range(n):
        row = []
        for x in range(n):
            row.append('-');
        solution.append(row);

    solution_found = False
    failed = False
    while not solution_found and not failed:
        solution[current[1]][current[0]] = letter

        if letter == 'z':
            solution_found = True
            break

        letter = chr(ord(letter) + 1)

        for i in range(len(MOVES)):
            next = [current[0] + MOVES[i][0], current[1] + MOVES[i][1]]

            if next[0] < 0:     continue
            if next[0] >= n:    continue
            if next[1] < 0:     continue
            if next[1] >= n:    continue

            if matrix[next[1]][next[0]] == letter:
                current = next
                failed = False
                break
            else:
                failed = True

    if solution_found:
        for y in solution:
            for x in y:
                print(x, end="")
            print()
    return solution_found

for i in range(n):
    m = input()
    row = []
    for j in m:
        row.append(j)
    matrix.append(row)

current = [-1, -1]
solution_found = False
for y in range(n):
    for x in range(n):
        if matrix[y][x] == 'a' and not solution_found:
            current[0] = x
            current[1] = y
            solution_found = solve(current)
