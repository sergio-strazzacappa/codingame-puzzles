NEIGHBORS = [
    [+1, -1],
    [+1, +1],
    [-1, +1],
    [-1, -1]
]

def sim(grid, frontier:list, max_infected):
    infected = len(frontier)

    while (len(frontier) > 0):
        C = frontier.pop(0)

        for i in range(4):
            next = [C[0] + NEIGHBORS[i][0], C[1] + NEIGHBORS[i][1]]

            if next[0] < 0:                     continue
            if next[0] >= n:                    continue
            if next[1] < 0:                     continue
            if next[1] >= n:                    continue
            if grid[next[1]][next[0]] == 'H':   continue
            if grid[next[1]][next[0]] == 'C':   continue

            # Infect the next cell
            frontier.append([next[0], next[1]])
            grid[next[1]][next[0]] = 'C'
            infected += 1

    if infected > max_infected:
        max_infected = infected
        return grid, max_infected

    return [], 0


n = int(input())
g = int(input())
solution = []
max_infected = 0
index = 0

for i in range(g):
    grid = []
    frontier = []

    for y in range(n):
        row = input()
        grid.append([])
        for x in range(len(row)):
            grid[-1].append(row[x])
            if row[x] == 'C':
                frontier.append([x, y])
    
    simulation = sim(grid, frontier, max_infected)

    if len(simulation[0]) > 0:
        solution = simulation[0]
        max_infected = simulation[1]
        index = i

print(index)

for y in solution:
    for x in y:
        print(x, end="")
    print()
