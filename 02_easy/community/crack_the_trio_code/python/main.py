def is_solution(a, b, c, n):
    return a == n or b == n or c == n or a + a == n or a + b == n or \
        a + c == n or b + b == n or b + c == n or c + c == n or \
        a + a + a == n or a + a + b == n or a + a + c == n or \
        a + b + b == n or a + b + c == n or a + c + c == n or \
        b + b + b == n or b + b + c == n or b + c + c == n or c + c + c == n


l = list(map(int, input().split(',')))

triads = 0;
aa = bb = cc = 0

for a in range(l[-1]):
    for b in range(a, l[-1]):
        for c in range(b, l[-1]):
            flag = True
            for n in l:
                if not is_solution(a, b, c, n):
                    flag = False
                    break
            if flag:
                triads += 1
                aa = a
                bb = b
                cc = c

if triads > 1:
    print("many")
elif triads == 0:
    print("none")
else:
    print(aa, bb, cc, sep=',')
