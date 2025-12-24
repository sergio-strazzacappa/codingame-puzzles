def set(instrs):
    for i in instrs:
        key, value = i.split('=')
        data[key] = value


def get(instrs):
    for i in instrs:
        if i not in data:
            print("null", end="")
        else:
            print(data[i], end="")

        if i == instrs[-1]:
            print(end="\n")
        else:
            print(end=" ")


def exists(instrs):
    for i in instrs:
        if i in data:
            print("true", end="")
        else:
            print("false", end="")

        if i == instrs[-1]:
            print(end="\n")
        else:
            print(end=" ")


def keys():
    if len(data) == 0:
        print("EMPTY")
        return
    
    for k in data.keys():
        print(k, end="")

        if k == list(data.keys())[-1]:
            print(end="\n")
        else:
            print(end=" ")
        

n = int(input())
data = {}

for i in range(n):
    s = input().split(' ')

    if s[0] == "SET":
        set(s[1:])
    elif s[0] == "GET":
        get(s[1:])
    elif s[0] == "EXISTS":
        exists(s[1:])
    else:
        keys()
