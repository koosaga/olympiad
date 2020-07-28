# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1101
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	a,b = sorted([int(i) for i in raw_input().split(" ")])
	if a <= 0 or b <= 0:
		break
	else:
		print "%s Sum=%d" % (str(range(a,b+1))[1:-1].replace(",",""),sum(xrange(a,b+1)))
