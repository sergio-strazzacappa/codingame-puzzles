from collections import deque

symbols = {}
queue = deque()
circuit = ""

n = int(input())

for i in range(n):
    inputs = input().split()
    name = inputs[0]
    r = int(inputs[1])
    symbols[name] = r

circuit = input()

for i in circuit.split(' '):
    # Parse subexpression, append the resistor
    if i != ')' and i != ']':
        queue.append(i)
        continue

    # End of subexpression, compute the resistor
    match = ''

    if i == ')':
        match = '('
    if i == ']':
        match = '['

    element = queue.pop()
    result = 0

    while (element != match):
        value = 0
        if type(element) is float:
            value = element
        else:
            value = symbols[element]

        if match == '(':
            result += value
        if match == '[':
            result += 1 / value
        element = queue.pop()

    # Append the result
    if match == '(':
        queue.append(float(result))
    if match == '[':
        queue.append(float(1 / result))

print(round(queue.pop(), 1))
