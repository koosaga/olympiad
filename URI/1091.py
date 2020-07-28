# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1091
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	casos = int(raw_input())
	if casos == 0:
		break
	else:
		xd,yd = [int(i) for i in raw_input().split(" ")]
		for i in xrange(casos):
			x,y = [int(k) for k in raw_input().split(" ")]
			if x==xd or y==yd:
				print "divisa"
			elif x > xd and y > yd:
				print "NE"
			elif x > xd and y < yd:
				print "SE"
			elif x < xd and y < yd:
				print "SO"
			else:
				print "NO"
