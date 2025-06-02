a = input().split(" ")
b = input().split(" ")

def unpack(string, values, rep):
    first = ""

    for num in string:
        if first == "":
            first = num
        else:
            rep.append(int(first))
            values.append(int(num))
            first = ""

a_values    = []
a_rep       = []
b_values    = []
b_rep       = []

unpack(a, a_values, a_rep)
unpack(b, b_values, b_rep)

sum = 0
for av, ar in zip(a_values, a_rep):
    for bv, br in zip(b_values, b_rep):
        if ar == 0:
            break
        if br == 0:
            continue
        if ar <= br:
            sum += av * bv * ar
            a_rep[a_rep.index(ar)] -= ar;
            b_rep[b_rep.index(br)] -= ar;
            br -= ar
            ar = 0
        else:
            sum += av * bv * br
            a_rep[a_rep.index(ar)] -= br;
            b_rep[b_rep.index(br)] -= br;
            ar -= br
            br = 0

print(sum)
