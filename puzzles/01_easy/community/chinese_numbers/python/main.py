numbers = []
for i in range(5):
    line = input().split(' ')

    if i == 0:
        numbers = [[] for j in range(len(line))]

    index = -1

    for n in line:
        index += 1
        if len(numbers[index]) == 1:
            continue
        if n == "*000*" and len(numbers[index]) == 0:
            numbers[index] = [0]
            continue
        if n == "*****" and len(numbers[index]) == 0:
            numbers[index] = [1]
            continue
        if n == "00000" and len(numbers[index]) == 0:
            numbers[index] = [2, 3, 4, 5]
            continue
        if n == "*****" and len(numbers[index]) == 4:
            numbers[index] = [2, 3]
            continue
        if n == "*****" and len(numbers[index]) == 2:
            numbers[index] = [2]
            continue
        if n == "*000*" and len(numbers[index]) == 2:
            numbers[index] = [3]
            continue
        if n == "0*0*0" and len(numbers[index]) == 4:
            numbers[index] = [4]
            continue
        if n == "**0**" and len(numbers[index]) == 4:
            numbers[index] = [5]
            continue
        if n == "**0**" and len(numbers[index]) == 0:
            numbers[index] = [6, 7, 9]
            continue
        if n == "00000" and len(numbers[index]) == 3:
            numbers[index] = [6, 7]
            continue
        if n == "*0*0*" and len(numbers[index]) == 2:
            numbers[index] = [6]
            continue
        if n == "**0**" and len(numbers[index]) == 2:
            numbers[index] = [7]
            continue
        if n == "*0*0*" and len(numbers[index]) == 0:
            numbers[index] = [8]
            continue
        if n == "0000*" and len(numbers[index]) == 3:
            numbers[index] = [9]
            continue


print(''.join([str(elem) for sublist in numbers for elem in sublist]))
