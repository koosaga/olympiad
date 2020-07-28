# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci06c2p4

N = int(input())
ans = 0

for i in range(1,N+1):
	for j in range(i+2,N+1):
		a = j - i - 1
		b = N - a - 2
		ans += a*b

print(ans//2)