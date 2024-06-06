n = int(input())

temp = float('inf')

for i in input().split():
    t = int(i)

    if t > 0 and temp > 0 and t <= temp:
        temp = t
    elif t > 0 and temp < 0 and -t >= temp:
        temp = t
    elif t < 0 and temp > 0 and -t < temp:
        temp = t
    elif t < 0 and temp < 0 and t > temp:
        temp = t

if temp == float('inf'):
    temp = 0

print(temp)