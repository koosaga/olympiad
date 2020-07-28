# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1176
#!/usr/bin/env python2.7
ordem = int(raw_input())
array = []
for i in xrange(ordem):
	array.append(int(raw_input()))
fib = [0,1,1]
maximo = max(array)
for i in xrange(3,maximo+1):
	fib.append(fib[i-1] + fib[i-2])
for number in array:
	print "Fib(%d) = %d" % (number,fib[number])
