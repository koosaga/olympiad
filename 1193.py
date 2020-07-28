# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1193
#!/usr/bin/env python2.7
# encoding : utf-8
ordem  = int(raw_input())
def receber(lista):
	return int(lista[0],{"dec":10,"bin":2,"hex":16}[lista[1]]),lista[1]
def exibir(x,y):
	if y == "dec":
		print "%s hex" % (hex(x)[2:])
		print "%s bin" % (bin(x)[2:])
	elif y == "bin":
		print "%d dec" % x
		print "%s hex" % (hex(x)[2:])
	else:
		print "%d dec" % x
		print "%s bin" % (bin(x)[2:])
for caso in xrange(1,ordem+1):
	a,b = receber(raw_input().split(" "))
	print "Case %d:" % caso
	exibir(a,b)
	print ""
