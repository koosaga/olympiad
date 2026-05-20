k, n = map(int, input().split())
que = [(0, 0, 1)]
vis = {0}

def good(x):
	return (x > 0) and (x not in vis)

for i in range(0, 1000000):
	x, y, z = que[i]
	if good(x) and good(y) and good(z):
		vis.add(x)
		vis.add(y)
		vis.add(z)
		print(str(x) + " " + str(y) + " " + str(z))
		n -= 1
	if n == 0:
		break
	que.append((x, z, k * (x + z) - x))
	que.append((y, z, k * (y + z) - y))
