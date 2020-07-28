# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1181
#!/usr/bin/env python2.7
linha = int(raw_input())
array = [[0 for j in xrange(12)] for k in xrange(12)]
operacao = raw_input()
for p in xrange(12):
	for k in xrange(12):
		array[p][k]=float(raw_input())
if operacao == "S":
	print "%.1f" % (sum(array[linha]))
else:
	print "%.1f" % (sum(array[linha])/12.0)
