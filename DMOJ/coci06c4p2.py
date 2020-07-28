# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci06c4p2
a,b,c,d = [int(i) for i in input().split()]

for linha in range(a):
	entrada = [i*d for i in input()]
	for i in range(c):
		print("".join(entrada))
