# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1983
#!/usr/bin/env python2.7
# encoding : utf-8
array = []
ordem = int(raw_input())
for i in xrange(ordem):
	a,b = [float(i) for i in raw_input().split(" ")]
	array.append(a+b*1j)
array.sort(key=lambda x: x.imag)
maximo = array[-1]
if maximo.imag >= 8:
	print int(maximo.real)
else:
	print "Minimum note not reached"
