from math import ceil

n = int(input())

for i in range(n):
    row, col, is_white = [int(j) for j in input().split()]

    chessboards = (row - 7) * (col - 7)

    if not is_white:
        chessboards -= 1
    
    chessboards = ceil(chessboards / 2)

    print(chessboards)
