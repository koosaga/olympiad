// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c1p3
alfabeto = "abcdefghijklmnopqrstuvwxyz"
shift = {}
shift["a"] = "z"
for i in xrange(1,len(alfabeto)):
	shift[alfabeto[i]] = alfabeto[i-1]
a = raw_input()
b = raw_input()
for i in xrange(26):
	if b in a:
		print i
		print a
		break
	a = "".join([shift[j] for j in a])