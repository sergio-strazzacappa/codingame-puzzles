def solve(line):
    stacks = []
    for container in line:
        new_stack = True
        for i in range(len(stacks)):
            if container <= stacks[i]:
                stacks[i] = container
                new_stack = False
                break
        if new_stack:
            stacks.append(container)
    print(len(stacks))


n = int(input())

for i in range(n):
    line = input()
    solve(line)
