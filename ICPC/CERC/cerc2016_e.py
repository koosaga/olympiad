k, n = map(int, input().split())
que = [(0, 1, k)]
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
	que.append((k * (y + z) - x, y, z))
	que.append((x, k * (x + z) - y, z))
	que.append((x, y, k * (x + y) - z))
