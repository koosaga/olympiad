# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci06c3p2

def abs_pares(a,b):
	return abs(a[0] - b[0]) + abs(a[1] - b[1])

dicio = {
	"A" : (0,0), "B" : (0,1), "C" : (0,2), "D" : (0,3),
	"E" : (1,0), "F" : (1,1), "G" : (1,2), "H" : (1,3),
	"I" : (2,0), "J" : (2,1), "K" : (2,2), "L" : (2,3),
	"M" : (3,0), "N" : (3,1), "O" : (3,2), "." : (3,3)
}

ans = 0

for i in range(4):
	entrada = input()
	for j,c in enumerate(entrada):
		if c == ".":
			continue
		ans += abs_pares((i,j), dicio[c])

print(ans)