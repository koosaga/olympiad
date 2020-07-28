# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci09c1p2

n = int(input())
ans = 0

for i in range(n+1):
	for j in range(i,n+1):
		ans += i + j

print(ans)