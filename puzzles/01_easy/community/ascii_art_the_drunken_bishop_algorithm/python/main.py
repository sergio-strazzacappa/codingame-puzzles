def to_binary(hexadecimal):
    if hexadecimal <= "9":
        decimal = int(hexadecimal)
    else:
        decimal = ord(hexadecimal) - ord("a") + 10

    binary = ""
    while decimal > 0:
        binary = str(decimal % 2) + binary
        decimal //= 2

    while len(binary) < 4:
        binary = "0" + binary

    return binary

def move(binary):
    if binary == "00": # UP-LEFT
        if pos[0] != 0 or pos[1] != 0:
            pos[0] += DIRS[0][0]
            pos[1] += DIRS[0][1]
            if pos[0] == -1:
                pos[0] = 0
            elif pos[1] == -1:
                pos[1] = 0
    elif binary == "01": # UP-RIGHT
        if pos[0] != COLS - 1 or pos[1] != 0:
            pos[0] += DIRS[1][0]
            pos[1] += DIRS[1][1]
            if pos[0] == COLS:
                pos[0] = COLS - 1
            elif pos[1] == -1:
                pos[1] = 0
    elif binary == "10": # DOWN-LEFT
        if pos[0] != 0 or pos[1] != ROWS - 1:
            pos[0] += DIRS[2][0]
            pos[1] += DIRS[2][1]
            if pos[0] == -1:
                pos[0] = 0
            elif pos[1] == ROWS:
                pos[1] = ROWS - 1
    elif binary == "11": # DOWN-RIGHT
        if pos[0] != COLS - 1 or pos[1] != ROWS - 1:
            pos[0] += DIRS[3][0]
            pos[1] += DIRS[3][1]
            if pos[0] == COLS:
                pos[0] = COLS - 1
            elif pos[1] == ROWS:
                pos[1] = ROWS - 1

    if board[pos[1]][pos[0]] != 'S':
        board[pos[1]][pos[0]] = str(int(board[pos[1]][pos[0]]) + 1)

def code(x, y):
    if board[y][x] == 'S' or board[y][x] == 'E':
        return
    if int(board[y][x]) % 15 == 0:
        board[y][x] = " "
    elif int(board[y][x]) % 15 == 1:
        board[y][x] = "."
    elif int(board[y][x]) % 15 == 2:
        board[y][x] = "o"
    elif int(board[y][x]) % 15 == 3:
        board[y][x] = "+"
    elif int(board[y][x]) % 15 == 4:
        board[y][x] = "="
    elif int(board[y][x]) % 15 == 5:
        board[y][x] = "*"
    elif int(board[y][x]) % 15 == 6:
        board[y][x] = "B"
    elif int(board[y][x]) % 15 == 7:
        board[y][x] = "O"
    elif int(board[y][x]) % 15 == 8:
        board[y][x] = "X"
    elif int(board[y][x]) % 15 == 9:
        board[y][x] = "@"
    elif int(board[y][x]) % 15 == 10:
        board[y][x] = "%"
    elif int(board[y][x]) % 15 == 11:
        board[y][x] = "&"
    elif int(board[y][x]) % 15 == 12:
        board[y][x] = "#"
    elif int(board[y][x]) % 15 == 13:
        board[y][x] = "/"
    elif int(board[y][x]) % 15 == 14:
        board[y][x] = "^"

def format_output():
    print("+---[CODINGAME]---+")
    for y in range(ROWS):
        print("|", end="")
        for x in range(COLS):
            print(board[y][x], end="")
        print("|", end="\n")
    print("+-----------------+")


ROWS = 9
COLS = 17
DIRS = [
    [-1, -1], # UP-LEFT
    [+1, -1], # UP-RIGHT
    [-1, +1], # DOWN-LEFT
    [+1, +1]  # DOWN-RIGHT
]

fingerprint = input().split(':')
board = [
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17,
    ["0"] * 17
]

pos = [8, 4]

board[pos[1]][pos[0]] = "S"

for f in fingerprint:
    binary = to_binary(f[1])
    move(binary[2:])
    move(binary[:2])
    binary = to_binary(f[0])
    b1 = binary[:2]
    move(binary[2:])
    move(binary[:2])

board[pos[1]][pos[0]] = "E"

for y in range(ROWS):
    for x in range(COLS):
        code(x, y)

format_output();
