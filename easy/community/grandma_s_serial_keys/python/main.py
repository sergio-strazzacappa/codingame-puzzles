username = input()

total = 0
for c in username:
    total += ord(c)

seed = total * len(username) ^ 20480

first   = seed & 65535
second  = seed >> 16
third   = (ord(username[0]) + ord(username[-1])) * len(username)
final   = (first + second + third) % 65536

first   = hex(first).upper()[2:].rjust(4, '0')
second  = hex(second).upper()[2:].rjust(4, '0')
third   = hex(third).upper()[2:].rjust(4, '0')
final   = hex(final).upper()[2:].rjust(4, '0')

print(f"{first}-{second}-{third}-{final}")
