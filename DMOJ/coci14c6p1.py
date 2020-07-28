# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci14c6p1

N,X = [int(i) for i in input().split()]

age = []
wants = []
ans = 0

for i in range(N):
	a,b = [int(i) for i in input().split()]
	age.append(a)
	wants.append(b)

for j in range(N-1):
	if age[j] == age[j+1]:
		continue
	if age[j] > age[j+1] and wants[j] == 1 and wants[j+1] == 0:
		age[j],age[j+1] = age[j+1],age[j]
	elif age[j] < age[j+1] and wants[j+1] and wants[j] == 0: 
		age[j],age[j+1] = age[j+1],age[j]

for i in range(N):
	if wants[i] == 1 and age[i] <= X:
		ans += 1
	elif wants[i] == 0 and age[i] > X:
		ans += 1

print(ans)