ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

operation = input()
pseudo_random_number = int(input())

rotors = []
for i in range(3):
    rotor = input()
    rotors.append(rotor)

message = list(input())

if operation == "ENCODE":
    # Shift
    for i in range(len(message)):
        c = ALPHABET[(ord(message[i]) + pseudo_random_number - ord('A')) % 26]
        message[i] = c
        pseudo_random_number += 1
    
    # Apply the rotors
    for r in rotors:
        for i in range(len(message)):
            position = ord(message[i]) - ord('A')
            message[i] = r[position]
else:
    # Apply the rotors
    for r in rotors[::-1]:
        for i in range(len(message)):
            letter = r.index(message[i])
            message[i] = ALPHABET[letter]
    
    # Shift
    for i in range(len(message)):
        c = ALPHABET[(ord(message[i]) - pseudo_random_number - ord('A')) % 26]
        message[i] = c
        pseudo_random_number += 1

print(''.join(message))
