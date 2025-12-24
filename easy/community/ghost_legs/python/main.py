def get_position(row, pos):
    '''
    Return the correct position in the row after removing the '-'
    '''
    if row[0] != '|':
        # It is the last row
        return pos

    actual_pos = -1
    for c in row:
        actual_pos += 1
        if c == '|':
            pos -= 1
        if pos < 0:
            break
    return actual_pos


cols, rows = [int(i) for i in input().split()]
grid = []

for y in range(rows):
    line = input()
    grid.append(line)

c = -1
for label in grid[0].split():
    c += 1
    current_c = c
    for y in grid[1:]:
        y = y.replace(' ', '')
        new_c = get_position(y, current_c)
        if new_c > 0 and y[new_c - 1]  == '-':
            current_c -= 1
            continue
        if new_c < len(y) - 2 and y[new_c + 1] == '-':
            current_c += 1
            continue
        if y == grid[-1].replace(' ', ''):
            print(label, y[current_c], sep='')
