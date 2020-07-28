# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1943
#!/usr/bin/env python2.7
# encoding : utf-8
e = int(raw_input())
if e == 1:
	print "Top 1"
elif e <= 3:
	print "Top 3"
elif e <= 5:
	print "Top 5"
elif e <= 10:
	print "Top 10"
elif e <= 25:
	print "Top 25"
elif e <= 50:
	print "Top 50"
else:
	print "Top 100"
