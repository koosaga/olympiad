// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c3p1
n = int(raw_input())
resposta = 0
for i in xrange(n):
	a = [i for i in raw_input()]
	b = int(a[-1])
	a.pop(-1)
	c = int("".join(a))
	resposta += c**b
print resposta