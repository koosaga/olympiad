# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1216
#!/usr/bin/env python2.7
# encoding : utf-8
array = []
while True:
	try:
		nome = raw_input()
		array.append(float(raw_input()))
	except EOFError:
		break
print "%.1f" % (sum(array)/float(len(array)))
