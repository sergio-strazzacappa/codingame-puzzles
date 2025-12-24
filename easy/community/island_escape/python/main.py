DIRS = [
    [+0, -1],
    [+1, +0],
    [+0, +1],
    [-1, +0]
]

def BFS(my_x, my_y, map):
    frontier = [[my_x, my_y]]
    visited = []

    while frontier:
        # While the frontier has elements

        current = frontier.pop(0)
        visited.append(current) # Add the current cell to the visited list

        if map[current[1]][current[0]] == 0:
            # The ocean is reached
            print("yes")
            return
        
        for i in range(4):
            # Try to move to every direction
            next_x = current[0] + DIRS[i][0]
            next_y = current[1] + DIRS[i][1]

            if abs(map[current[1]][current[0]] - map[next_y][next_x]) <= 1:
                if [next_x, next_y] not in visited:
                    # If the differences is less or equal than 1 and is not
                    # visited add it to the frontier to continue the search
                    frontier.append([next_x, next_y])

    # If this point is reached no solution was found
    print("no")        

n = int(input())
map = []
my_x = my_y = n // 2

for y in range(n):
    row = []
    for x in input().split():
        elevation = int(x)
        row.append(elevation)
    map.append(row)

BFS(my_x, my_y, map)
