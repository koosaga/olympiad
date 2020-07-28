# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci07c2p2
melhor = 1
n = int(input())

for a in range(n+1):
	b = n - a
	melhor = max(melhor, (a+1)*(b+1))

print(melhor)
