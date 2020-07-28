# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1221
#!/usr/bin/env python2.7
# encoding : utf-8
def primo(x):
	return x==2 or x % 2 != 0 and all([x%i for i in xrange(3,int(x**0.5)+1,2)])
ordem = int(raw_input())
for j in xrange(ordem):
	i = int(raw_input())
	if primo(i):
		print "Prime"
	else:
		print "Not Prime"
