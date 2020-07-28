# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci07c1p3

def min_dist(X,Y):
	ans = abs(Y[0] - X)
	for Z in Y:
		ans = min(ans, abs(Z - X) )
	return ans

N = int(input())

P = sorted([int(i) for i in input().split()])
A,B = [int(i) for i in input().split()]

C = []

for i in range(N-1):
	L = (P[i]+P[i+1])//2
	C.append(L)
	C.append(L+1)
	C.append(L-1)

C.append(A)
C.append(A+1)
C.append(B)
C.append(B-1)

D = []
for i in C:
	if i < A or i > B:
		continue
	if i % 2 == 0:
		continue
	D.append((min_dist(i,P),i))

D.sort()
print(D[-1][1])