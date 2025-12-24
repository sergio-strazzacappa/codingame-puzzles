# Read the input
cols, rows              = [int(i) for i in input().split()]
start_row, start_col    = [int(i) for i in input().split()]
n                       = int(input())

# Store the maps
maps = []

for i in range(n):
    maps.append([])
    for y in range(rows):
        map_row = input()
        maps[i].append([])
        for x in map_row:
            maps[i][y].append(x)

# Solve the problem
shortest_path = [9999, -1]

for i in range(n):
    map = maps[i]
    current_col = start_col
    current_row = start_row
    path = 0
    success = False

    while not success:
        if current_row < 0:         break
        if current_row > rows - 1:  break
        if current_col < 0:         break
        if current_col > cols - 1:  break

        dir = maps[i][current_row][current_col]
        maps[i][current_row][current_col] = 'X'
    
        if dir == '>':
            current_col += 1
            path += 1
        elif dir == 'v':
            current_row += 1
            path += 1
        elif dir == '<':
            current_col -= 1
            path += 1
        elif dir == '^':
            current_row -= 1
            path += 1
        elif dir == 'T':
            success = True
            path += 1
            if path < shortest_path[0]:
                shortest_path = [path, i]
        else:
            break

# Print the answer
if shortest_path[1] == -1:
    print("TRAP")
else:
    print(shortest_path[1])
