# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1153
#!/usr/bin/env python2.7
# encoding : utf-8
def fatorial(x):
	if x == 0:
		return 1
	else:
		return x*fatorial(x-1)
print fatorial(int(raw_input()))
