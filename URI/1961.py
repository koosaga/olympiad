# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1961
#!/usr/bin/env python2.7
# encoding : utf-8
a,b = [int(i) for i in raw_input().split(" ") if i != ""]
array = [int(i) for i in raw_input().split(" ") if i != ""]
for i,j in zip(array[1:],array):
	if abs(i-j) > a:
		print "GAME OVER"
		break
else:
	print "YOU WIN"
