# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2062
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
array = raw_input().split()
for i in xrange(len(array)):
	t = array[i]
	if len(t) == 3:
		if "OB" in t:
			array[i] = "OBI"
		elif "UR" in t:
			array[i] = "URI"
print " ".join(array)
