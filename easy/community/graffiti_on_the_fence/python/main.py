l = int(input())
n = int(input())

ranges = []

for i in range(n):
    st, ed = [int(j) for j in input().split()]
    ranges.append([st, ed])

ranges.sort()

meter = 0
index = 0
all_painted = True

while meter <= l:
    if index == len(ranges):
        if ranges[-1][1] != l:
            print(meter, l)
            all_painted = False
        break
    if meter > ranges[index][1]:
        index += 1
        continue
    if meter >= ranges[index][0] and meter <= ranges[index][1]:
        meter = ranges[index][1]
        index += 1
        continue
    all_painted = False
    print(meter, ranges[index][0])
    meter = ranges[index][0]

if all_painted:
    print("All painted")
