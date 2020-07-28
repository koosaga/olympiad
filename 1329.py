# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1329
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	ordem = int(raw_input())
	if ordem == 0 :
		break
	else:
		array = [int(i) for i in raw_input().split(" ")]
		print "Mary won %d times and John won %d times" % (array.count(0),array.count(1))
