ERROR_NUM = -10001

n = int(input())
state = [ERROR_NUM] * n
pending = []

for i in range(n):
    operation, arg1, arg2 = input().split()
    pending.append([operation, arg1, arg2, i])

while len(pending) > 0:
    for op in pending:
        operation, arg1, arg2, i = op

        if arg1[0] == '$' and state[int(arg1[1:])] == ERROR_NUM:
            continue
        if arg2[0] == '$' and state[int(arg2[1:])] == ERROR_NUM:
            continue

        if arg1[0] == '$':
            arg1 = state[int(arg1[1:])]
        if arg2[0] == '$':
            arg2 = state[int(arg2[1:])]

        if operation == "VALUE":
            state[i] = int(arg1)
        if operation == "ADD":
            state[i] = int(arg1) + int(arg2)
        if operation == "SUB":
            state[i] = int(arg1) - int(arg2)
        if operation == "MULT":
            state[i] = int(arg1) * int(arg2)

        pending.remove(op)
        break

for s in state:
    print(s)
