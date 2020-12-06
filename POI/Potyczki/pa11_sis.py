def f(n, v):
	ret = (n % v + 1) * (n // v)
	n //= v
	ret += (n * (n - 1) // 2) * v
	return ret

n = int(input())
ret = 0
v = 5

while v <= n:
	ret += f(n, v)
	v *= 5

print(ret)
