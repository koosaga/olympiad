# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci07c4p1

def simulate(x,y,z):
	while True:
		x -= y
		if x <= 0:
			return 1
		x -= z
		if x <= 0:
			return 0

a,b,c,d = [int(i) for i in input().split()]
times = [int(i) for i in input().split()]

for t in times:
	print(["none","one","both"][simulate(t,a,b) + simulate(t,c,d)])