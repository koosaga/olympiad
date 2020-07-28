# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci14c7p4

def escolhe2(x):
	return (x*(x-1))//2

def escolhe3(x):
	return (x*(x-1)*(x-2))//6

N,K = [int(i) for i in input().split()]

if N == 1:
	com3 = escolhe3(K)*(3*(2**19) - 6)
	com2 = 2*escolhe2(K)
	print(com3 + com2)
elif N == 2:
	print(96*escolhe3(K))
elif N == 3:
	com3 = escolhe3(K)*(24 - 6)
	com2 = 2*escolhe2(K)
	print(com2+com3)
elif N == 4:
	com3 = escolhe3(K)*(3*(2**13) - 6)
	com2 = 2*escolhe2(K)
	print(com2 + com3)
elif N == 5:
	com3 = escolhe3(K)*(3*(2**2))
	print(com3)
elif N == 6:
	com3 = escolhe3(K)*6
	print(com3)
elif N == 7:
	com3 = escolhe3(K)*(3*(2**5))
	print(com3)
else:
	com3 = escolhe3(K)*((2**30) - 4)
	com2 = escolhe2(K)*2
	print(com3 + com2)