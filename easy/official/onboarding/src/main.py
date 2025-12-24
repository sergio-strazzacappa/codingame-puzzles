#! /usr/bin/env python3

while True:
    enemy1 = input(), int(input())
    enemy2 = input(), int(input())
    
    if enemy1[1] < enemy2[1]:
        print(enemy1[0])
    else:
        print(enemy2[0])
