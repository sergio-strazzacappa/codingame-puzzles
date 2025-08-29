tests = int(input())

for t in range(tests):
    address = input().split('/')

    # Parse the prefix
    prefix = address[0].split('.')
    tmp = []
    for n in prefix:
        tmp.append(format(int(n), '08b'))
    binary = str(''.join(tmp))

    # Parse the suffix
    suffix = int(address[1])

    variable_bits = 32 - suffix
    valid = True
    index = 0
    range = 0

    for n in binary[::-1]:
        if n != '0' and index < variable_bits:
            valid = False
        if n != '0' and not valid:
            break
        range += 1 
        index += 1

    if valid:
        print(f"valid {2 ** variable_bits}")
    else:
        print(f"invalid {'.'.join(prefix)}/{32 - range} {2 ** range}")
