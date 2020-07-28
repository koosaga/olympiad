# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1151
#!/usr/bin/env python2.7
# encoding : utf-8
fib = [0,1,1]
maximo = int(raw_input())
for i in xrange(3,maximo):
	fib.append(fib[i-1] + fib[i-2])
print " ".join([str(k) for k in fib])
