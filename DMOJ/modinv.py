# Ivan Carvalho
# Solution to https://dmoj.ca/problem/modinv
def egcd(a,b):
	if a == 0:
		return (b,0,1)
	else:
		g,x,y = egcd(b % a,a)
		return (g,y - (b // a)*x,x)
a,b = [int(i) for i in raw_input().split()]
c,d,e = egcd(a,b)
d += b
d %= b
print d