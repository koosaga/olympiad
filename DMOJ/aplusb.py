# Ivan Carvalho
# Solution to https://dmoj.ca/problem/aplusb
import sys
raw_input = sys.stdin.readline
tc = int(raw_input())
while tc:
    tc -= 1
    a,b = [int(i) for i in raw_input().split()]
    print a + b